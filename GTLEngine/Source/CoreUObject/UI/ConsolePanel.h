#pragma once
#include "CoreUObject/UI/UIBase.h"

class UConsolePanel: public UUIBase 
{
	DECLARE_CLASS(UConsolePanel, UUIBase)

public:
	UConsolePanel();
	// UUIBase을(를) 통해 상속됨
	void Tick(float TickTime) override;
	void Destroy() override;
	void ExecCommand(const char* s);
	void AddLog(const char* fmt, ...);
	void AddLog(const std::string str);
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
	TArray<FString> StrSplit(FString s);
};