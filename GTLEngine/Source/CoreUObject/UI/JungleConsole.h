#pragma once

#include "UI/UIBase.h"

#include "ImGui/imgui.h" // TODO: 아래 멤버 변수 중 ImGui의 구조체를 전방선언 하는 방법을 찾으면 cpp로 이동

struct FLogEntry;

class UJungleConsole: public UUIBase
{
public:
    explicit UJungleConsole(UUIManager* InUIManager);
    void Destroy() override;

private:
    char                   inputBuf[256];
    std::vector<FLogEntry> logEntries;
    ImVector<const char*>  commands;
    ImVector<char*>        history;
    int                    historyPos;    // -1: new line, 0..History.Size-1 browsing history.
    ImGuiTextFilter        textFilter;
    ImGuiTextFilter        categoryFilter;
    bool                   autoScroll;
    bool                   scrollToBottom;
    bool                   copy_to_clipboard;


private:
    void ClearLog();
    void AddLog(const char* category, int verbosity, const char* fmt, ...);
    
    void Draw() override;
    void DrawExplain();
    void DrawEditButtons();
    void DrawOptionButton();
    void DrawFilters();
    void DrawLogField();
    void DrawInputField();

    void ExecCommand(const char* command_line);
    static int TextEditCallbackStub(ImGuiInputTextCallbackData* data);
    int TextEditCallback(ImGuiInputTextCallbackData* data);

};