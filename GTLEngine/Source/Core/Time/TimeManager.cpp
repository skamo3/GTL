#include "pch.h"
#include "TimeManager.h"



void UTimeManager::Initialize()
{
	QueryPerformanceFrequency(&CpuFrequency);

	QueryPerformanceCounter(&PrevFrequency);
}

void UTimeManager::Update()
{
	QueryPerformanceCounter(&CurrentFrequency);

	float differenceFrequency = static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart);
	DeltaTimeValue = differenceFrequency / static_cast<float>(CpuFrequency.QuadPart);
	PrevFrequency.QuadPart = CurrentFrequency.QuadPart;
}
