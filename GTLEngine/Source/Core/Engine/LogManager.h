#pragma once
#include "EnginePch.h"


class ULogManager {
private:
	ULogManager() = default;
	~ULogManager() = default;
	ULogManager(ULogManager&) = delete;
	ULogManager& operator=(ULogManager&) = delete;
	ULogManager(ULogManager&&) = delete;
	ULogManager& operator=(ULogManager&&) = delete;
public:
	static ULogManager& GetLogManager() {
		static ULogManager Instance;
		return Instance;
	}

private:
	TArray<char*> Items;

public:
	static void AddLog(const wchar_t* fmt, ...);
	// static void AddLog(const char* fmt, ...);
	static void AddLog(FString str, ...);
	// static void AddLog(std::string s, ...);
	static void ClearLog();
	inline static TArray<char*> GetLogs() { return GetLogManager().Items; }
};