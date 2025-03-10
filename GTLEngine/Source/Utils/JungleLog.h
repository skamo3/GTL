#pragma once

struct ImVec4;

struct FLogEntry
{
    std::string category; // 로그 카테고리 (예: "LogTemp")
    std::string message;  // 로그 메시지
    int verbosity;        // 로그 레벨 (0: Verbose, 1: Log, 2: Warning, 3: Error)
};

extern const char* verbosityLevels[];

extern ImVec4 verbosityColors[];