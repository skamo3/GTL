#pragma once
#include <string>
#include <vector>

#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"


const char* verbosityLevels[] = {
    "", "Log", "Warning", "Error", "Display", "Fatal", "Verbose", "VeryVerbose", "Unkown"
};

ImVec4 verbosityColors[] = {
    ImVec4(0.4f, 0.4f, 0.4f, 1.0f),
    ImVec4(0.8f, 0.8f, 0.8f, 1.0f),
    ImVec4(1.0f, 0.647f, 0.0f, 1.0f),
    ImVec4(1.0f, 0.8f, 0.6f, 1.0f),
};

struct FLogEntry
{
    string category; // 로그 카테고리 (예: "LogTemp")
    string message;  // 로그 메시지
    int verbosity;        // 로그 레벨 (0: Verbose, 1: Log, 2: Warning, 3: Error)
};

class UJungleConsole {
public:
    UJungleConsole();
    ~UJungleConsole();

private:
    char                  inputBuf[256];
    vector<FLogEntry> logEntries;
    ImVector<const char*> commands;
    ImVector<char*>       history;
    int                   historyPos;    // -1: new line, 0..History.Size-1 browsing history.
    ImGuiTextFilter       textFilter;
    ImGuiTextFilter       categoryFilter;
    bool                  autoScroll;
    bool                  scrollToBottom;

private:
    void ClearLog();
    void AddLog(const char* category, int verbosity, const char* fmt, ...);
    void Draw(const char* title, bool* p_open);
    void ExecCommand(const char* command_line);
    static int TextEditCallbackStub(ImGuiInputTextCallbackData* data);
    int TextEditCallback(ImGuiInputTextCallbackData* data);

private:
    // Portable helpers
    static int   Stricmp(const char* s1, const char* s2) { int d; while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; } return d; }
    static int   Strnicmp(const char* s1, const char* s2, int n) { int d = 0; while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; n--; } return d; }
    static char* Strdup(const char* s) { IM_ASSERT(s); size_t len = strlen(s) + 1; void* buf = ImGui::MemAlloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)s, len); }
    static void  Strtrim(char* s) { char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }

};