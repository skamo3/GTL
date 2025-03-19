#include "pch.h"
#include "LogManager.h"

void ULogManager::AddLog(const wchar_t* fmt, ...) {
    wchar_t wbuf[1024];
    va_list args;

    va_start(args, fmt);
    _vsnwprintf_s(wbuf, ARRAYSIZE(wbuf), fmt, args);
    wbuf[ARRAYSIZE(wbuf) - 1] = 0;
    va_end(args);

    //char cbuf[1024];
    char* cbuf = new char[1024];
    WideCharToMultiByte(CP_ACP, 0, wbuf, ARRAYSIZE(wbuf), cbuf, 1024, nullptr, nullptr);
    GetLogManager().Items.push_back(cbuf);
}
/*
void ULogManager::AddLog(const char* fmt, ...) {
    char cbuf[1024];
    va_list args;

    va_start(args, fmt);
    vsnprintf_s(cbuf, ARRAYSIZE(cbuf), fmt, args);
    cbuf[ARRAYSIZE(cbuf) - 1] = 0;
    va_end(args);

    GetLogManager().Items.push_back(cbuf);
}
*/
void ULogManager::AddLog(FString fmt, ...) {
    va_list args;
    va_start(args, fmt);
    AddLog(fmt.c_str(), args);
    va_end(args);
}
/*
void ULogManager::AddLog(std::string fmt, ...) {
    va_list args;
    va_start(args, fmt);
    AddLog(fmt.c_str(), args);
    va_end(args);
}
*/
void ULogManager::ClearLog() {
    TArray<char*> item = GetLogManager().Items;
    for ( int i = 0; i < item.size(); i++ )
        delete item[i];
    GetLogManager().Items.clear();
}
