#include "pch.h"
#include "TimeManager.h"

LARGE_INTEGER UTimeManager::CpuFrequency = {};
LARGE_INTEGER UTimeManager::PrevFrequency = {};
LARGE_INTEGER UTimeManager::CurrentFrequency = {};
float UTimeManager::DeltaTimeValue = 0;


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
