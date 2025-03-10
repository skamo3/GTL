#pragma once

class UTimeManager
{
public:
	static void Initialize();
	static void Update();

	inline static float DeltaTime() { return DeltaTimeValue; }

private:
	static LARGE_INTEGER CpuFrequency;
	static LARGE_INTEGER PrevFrequency;
	static LARGE_INTEGER CurrentFrequency;
	static float DeltaTimeValue;
};

