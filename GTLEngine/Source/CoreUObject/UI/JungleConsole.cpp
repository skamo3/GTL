#include "pch.h"
#include "JungleConsole.h"
#include <format>

// ImGui include.
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGuiStringLibrary.h"

#include "Utils/JungleLog.h"


UJungleConsole::UJungleConsole(UUIManager* InUIManager) : UUIBase(InUIManager)
{
    ClearLog();
    memset(inputBuf, 0, sizeof(inputBuf));
    historyPos = -1;

    // "CLASSIFY" is here to provide the test case where "C"+[tab] completes to "CL" and display multiple matches.
    commands.push_back("HELP");
    commands.push_back("HISTORY");
    commands.push_back("CLEAR");
    commands.push_back("CLASSIFY");
    autoScroll = true;
    scrollToBottom = false;
    AddLog("", 1, "Welcome to Dear ImGui!");
}

void UJungleConsole::Destroy()
{
    ClearLog();
    for (int i = 0; i < history.Size; i++)
        ImGui::MemFree(history[i]);

    UUIBase::Destroy();
}

void UJungleConsole::ClearLog()
{
    logEntries.clear();
}

void UJungleConsole::AddLog(const char* category, int verbosity, const char* fmt, ...)
{
    char buf[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
    buf[IM_ARRAYSIZE(buf) - 1] = 0;
    va_end(args);

    // 새로운 로그 엔트리 생성 및 logEntries 벡터에 추가
    FLogEntry entry;
    entry.category = category;
    entry.verbosity = verbosity;
    entry.message = buf;
    logEntries.push_back(entry);
}


void UJungleConsole::Draw()
{
    ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
    bool p_open = true;
    if (!ImGui::Begin("JungleConsole", &p_open))
    {
        ImGui::End();
        return;
    }

    // As a specific feature guaranteed by the library, after calling Begin() the last Item represent the title bar.
    // So e.g. IsItemHovered() will return true when hovering the title bar.
    // Here we create a context menu only available from the title bar.
    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::MenuItem("Close Console"))
            p_open = false;
        ImGui::EndPopup();
    }

    DrawExplain();
    DrawEditButtons();
    DrawOptionButton();
    DrawFilters();
    DrawLogField();
    DrawInputField();


    ImGui::End();
}

void UJungleConsole::DrawExplain()
{
    ImGui::TextWrapped(
        "This example implements a console with basic coloring, completion (TAB key) and history (Up/Down keys). A more elaborate "
        "implementation may want to store entries along with extra data such as timestamp, emitter, etc.");
    ImGui::TextWrapped("Enter 'HELP' for help.");
}

void UJungleConsole::DrawEditButtons()
{
    if (ImGui::SmallButton("Add Debug Text")) 
    { 
        AddLog("LogTemp", 0, "verbosity 0 text", logEntries.size()); 
        AddLog("LogTemp", 1, "verbosity 1 text"); 
        AddLog("LogTemp", 2, "verbosity 2 Text!");
    }
    ImGui::SameLine();

    if (ImGui::SmallButton("Add Debug Error")) 
    {
        AddLog("LogTemp", 2, "something went wrong");
    }
    ImGui::SameLine();

    if (ImGui::SmallButton("Clear")) 
    { 
        ClearLog(); 
    }
    ImGui::SameLine();
    copy_to_clipboard = ImGui::SmallButton("Copy");
    //static float t = 0.0f; if (ImGui::GetTime() - t > 0.02f) { t = ImGui::GetTime(); AddLog("Spam %f", t); }

    ImGui::Separator();
}

void UJungleConsole::DrawOptionButton()
{
    // Options menu
    if (ImGui::BeginPopup("Options"))
    {
        ImGui::Checkbox("Auto-scroll", &autoScroll);
        ImGui::EndPopup();
    }
    // Options, Filter
    ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_O, ImGuiInputFlags_Tooltip);
    if (ImGui::Button("Options"))
        ImGui::OpenPopup("Options");
    ImGui::SameLine();
}

void UJungleConsole::DrawFilters()
{
    textFilter.Draw("Text Filter", 180);
    ImGui::SameLine();
    categoryFilter.Draw("Category Filter", 180);
    ImGui::Separator();
}

void UJungleConsole::DrawLogField()
{
    // Reserve enough left-over height for 1 separator + 1 input text
    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), ImGuiChildFlags_NavFlattened, ImGuiWindowFlags_HorizontalScrollbar))
    {
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::Selectable("Clear")) ClearLog();
            ImGui::EndPopup();
        }


        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
        if (copy_to_clipboard)
            ImGui::LogToClipboard();
        for (const auto& entry : logEntries)
        {
            if (textFilter.IsActive() && categoryFilter.IsActive()) 
            {
                if (!textFilter.PassFilter(entry.message.c_str()) 
                    && !categoryFilter.PassFilter(entry.category.c_str()))
                    continue;
            }
            else if (textFilter.IsActive()) 
            {
                if (!textFilter.PassFilter(entry.message.c_str()))
                    continue;
            }
            else if (categoryFilter.IsActive()) 
            {
                if (!categoryFilter.PassFilter(entry.category.c_str()))
                    continue;
            }

            ImGui::PushStyleColor(ImGuiCol_Text, verbosityColors[(entry.verbosity > 2) ? 3 : entry.verbosity]);


            std::string out = "";

            if (entry.category != "") 
            {
                out += entry.category + ": ";
            }

            // verbosity 변환
            std::string verbosityStr = verbosityLevels[(entry.verbosity > 7) ? 8 : entry.verbosity];

            if (entry.verbosity != 0) 
            {
                out += verbosityStr + ": ";
            }

            // 최종 출력할 문자열 조합: "Category: Verbosity message"
            out += entry.message;
            ImGui::TextUnformatted(out.c_str());

            ImGui::PopStyleColor();
        }
        if (copy_to_clipboard)
            ImGui::LogFinish();
        // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
        // Using a scrollbar or mouse-wheel will take away from the bottom edge.
        if (scrollToBottom || (autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
            ImGui::SetScrollHereY(1.0f);
        scrollToBottom = false;

        ImGui::PopStyleVar();
    }
    ImGui::EndChild();
    ImGui::Separator();

}

void UJungleConsole::DrawInputField()
{
    // Command-line
    bool reclaim_focus = false;
    bool showRelatedWindow = false;
    // 후보 목록을 담을 ImVector 생성 (ImGui에서 사용하는 컨테이너)
    ImVector<const char*> suggestions;

    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
    if (ImGui::InputText("Input", inputBuf, IM_ARRAYSIZE(inputBuf), input_text_flags, &TextEditCallbackStub, (void*)this))
    {
        char* s = inputBuf;
        UImGuiStringLibrary::Strtrim(s);
        if (s[0]) {
            ExecCommand(s);
        }
        strcpy_s(s, IM_ARRAYSIZE(inputBuf), "");
        reclaim_focus = true;
    }
    else {
        // 사용자가 입력 중이라면 InputBuf가 비어있지 않을 것입니다.
        // 입력된 텍스트와 접두사가 일치하는 명령어 후보를 찾습니다.

        if (strlen(inputBuf) > 0)
        {
            for (int i = 0; i < commands.Size; i++)
            {
                // ImStrnicmp는 대소문자 구분 없이 문자열 비교합니다.
                // inputBuf가 명령어의 앞부분과 일치하면 후보 목록에 추가합니다.
                if (ImStrnicmp(inputBuf, commands[i], (int)strlen(inputBuf)) == 0)
                {
                    suggestions.push_back(commands[i]);
                }
            }
        }

        if (suggestions.Size > 0)
        {
            showRelatedWindow = true;

            // InputText 위에 창을 띄우기 위해 InputText의 위치를 가져옵니다.
            ImVec2 pos = ImGui::GetItemRectMin();

            float lineHeight = ImGui::GetTextLineHeight();
            float lineHeightWithSpacing = ImGui::GetTextLineHeightWithSpacing();
            float totalHeight = lineHeightWithSpacing * (suggestions.Size - 1) + lineHeight;

            pos.y -= totalHeight + 22;

            ImGui::SetNextWindowPos(pos);
            ImGui::BeginTooltip();
            for (int i = 0; i < suggestions.Size; i++)
            {
                ImGui::Text("%s", suggestions[i]);
            }
            ImGui::EndTooltip();
        }
    }

    // Auto-focus on window apparition
    ImGui::SetItemDefaultFocus();
    if (reclaim_focus)
        ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
}

void UJungleConsole::ExecCommand(const char* command_line)
{
    AddLog("", 0, "# %s\n", command_line);

    // Insert into history. First find match and delete it so it can be pushed to the back.
    // This isn't trying to be smart or optimal.
    historyPos = -1;
    for (int i = history.Size - 1; i >= 0; i--)
        if (UImGuiStringLibrary::Stricmp(history[i], command_line) == 0)
        {
            ImGui::MemFree(history[i]);
            history.erase(history.begin() + i);
            break;
        }
    history.push_back(UImGuiStringLibrary::Strdup(command_line));

    // Process command
    if (UImGuiStringLibrary::Stricmp(command_line, "CLEAR") == 0)
    {
        ClearLog();
    }
    else if (UImGuiStringLibrary::Stricmp(command_line, "HELP") == 0)
    {
        AddLog("", 1, "Commands:");
        for (int i = 0; i < commands.Size; i++)
            AddLog("", 1, "- %s", commands[i]);
    }
    else if (UImGuiStringLibrary::Stricmp(command_line, "HISTORY") == 0)
    {
        int first = history.Size - 10;
        for (int i = first > 0 ? first : 0; i < history.Size; i++)
            AddLog("", 1, "%3d: %s\n", i, history[i]);
    }
    else
    {
        AddLog("", 2, "Unknown command: '%s'\n", command_line);
    }

    // On command input, we scroll to bottom even if autoscroll==false
    scrollToBottom = true;
}

int UJungleConsole::TextEditCallbackStub(ImGuiInputTextCallbackData* data)
{
    UJungleConsole* console = (UJungleConsole*)data->UserData;
    return console->TextEditCallback(data);
}


int UJungleConsole::TextEditCallback(ImGuiInputTextCallbackData* data)
{
    //AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
    switch (data->EventFlag)
    {
    case ImGuiInputTextFlags_CallbackCompletion:
    {
        // Example of TEXT COMPLETION

        // Locate beginning of current word
        const char* word_end = data->Buf + data->CursorPos;
        const char* word_start = word_end;
        while (word_start > data->Buf)
        {
            const char c = word_start[-1];
            if (c == ' ' || c == '\t' || c == ',' || c == ';')
                break;
            word_start--;
        }

        // Build a list of candidates
        ImVector<const char*> candidates;
        for (int i = 0; i < commands.Size; i++)
            if (UImGuiStringLibrary::Strnicmp(commands[i], word_start, (int)(word_end - word_start)) == 0)
                candidates.push_back(commands[i]);

        if (candidates.Size == 0)
        {
            // No match
            AddLog("", 2, "No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
        }
        else if (candidates.Size == 1)
        {
            // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
            data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
            data->InsertChars(data->CursorPos, candidates[0]);
            data->InsertChars(data->CursorPos, " ");
        }
        else
        {
            // Multiple matches. Complete as much as we can..
            // So inputing "C"+Tab will complete to "CL" then display "CLEAR" and "CLASSIFY" as matches.
            int match_len = (int)(word_end - word_start);
            for (;;)
            {
                int c = 0;
                bool all_candidates_matches = true;
                for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
                    if (i == 0)
                        c = toupper(candidates[i][match_len]);
                    else if (c == 0 || c != toupper(candidates[i][match_len]))
                        all_candidates_matches = false;
                if (!all_candidates_matches)
                    break;
                match_len++;
            }

            if (match_len > 0)
            {
                data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
            }

            // List matches
            AddLog("", 1, "Possible matches:\n");
            for (int i = 0; i < candidates.Size; i++)
                AddLog("", 1, "- %s\n", candidates[i]);
        }

        break;
    }
    case ImGuiInputTextFlags_CallbackHistory:
    {
        // Example of HISTORY
        const int prev_history_pos = historyPos;
        if (data->EventKey == ImGuiKey_UpArrow)
        {
            if (historyPos == -1)
                historyPos = history.Size - 1;
            else if (historyPos > 0)
                historyPos--;
        }
        else if (data->EventKey == ImGuiKey_DownArrow)
        {
            if (historyPos != -1)
                if (++historyPos >= history.Size)
                    historyPos = -1;
        }

        // A better implementation would preserve the data on the current input line along with cursor position.
        if (prev_history_pos != historyPos)
        {
            const char* history_str = (historyPos >= 0) ? history[historyPos] : "";
            data->DeleteChars(0, data->BufTextLen);
            data->InsertChars(0, history_str);
        }
    }
    }
    return 0;
}

