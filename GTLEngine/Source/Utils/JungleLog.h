#pragma once
#include <string>
#include "ImGui/imgui.h"


struct FLogEntry
{
    std::string category; // 로그 카테고리 (예: "LogTemp")
    std::string message;  // 로그 메시지
    int verbosity;        // 로그 레벨 (0: Verbose, 1: Log, 2: Warning, 3: Error)
};

const char* verbosityLevels[] = {
    "", "Log", "Warning", "Error", "Display", "Fatal", "Verbose", "VeryVerbose", "Unkown"
};

ImVec4 verbosityColors[] = {
    ImVec4(0.4f, 0.4f, 0.4f, 1.0f),
    ImVec4(0.8f, 0.8f, 0.8f, 1.0f),
    ImVec4(1.0f, 0.647f, 0.0f, 1.0f),
    ImVec4(1.0f, 0.8f, 0.6f, 1.0f),
};