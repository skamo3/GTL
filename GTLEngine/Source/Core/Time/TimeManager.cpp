#include "pch.h"
#include "TimeManager.h"

#include "Engine.h"

using namespace std;

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
	UEngine::GetEngine().SetFPS(1.0f / DeltaTimeValue);

	PrevFrequency.QuadPart = CurrentFrequency.QuadPart;
}
