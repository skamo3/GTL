
#include "pch.h"
#include "Utils/JungleLog.h"

#include "ImGui/imgui.h"

const char* verbosityLevels[] = {
    "",
    "Log",
    "Warning",
    "Error",
    "Display",
    "Fatal",
    "Verbose",
    "VeryVerbose",
    "Unkown"
};

ImVec4 verbosityColors[] = {
    ImVec4(0.4f, 0.4f, 0.4f, 1.0f),
    ImVec4(0.8f, 0.8f, 0.8f, 1.0f),
    ImVec4(1.0f, 0.647f, 0.0f, 1.0f),
    ImVec4(1.0f, 0.8f, 0.6f, 1.0f),
};