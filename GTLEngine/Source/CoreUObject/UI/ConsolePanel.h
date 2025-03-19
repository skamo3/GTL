#pragma once
#include "CoreUObject/UI/UIBase.h"

class UConsolePanel: public UUIBase {
public:
	UConsolePanel();
	// UUIBase을(를) 통해 상속됨
	void Tick(float TickTime) override;
	void Destroy() override;

	void ExecCommand(const char* s);
	void AddLog(const char* fmt, ...);
	void ClearLog();
private:
	float WindowWidth;
	float WindowHeight;
	char InputBuffer[256];
	ImVector<char*> Items;

	int Stricmp(const char* s1, const char* s2);
	int Strnicmp(const char* s1, const char* s2, int n);
	char* Strdup(const char* s);
	void Strtrim(char* s);
	TArray<std::string> StrSplit(std::string s);

	// command functions
	FString Spawn(TArray<FString> commands);
	FString Delete(TArray<FString> commands);
};