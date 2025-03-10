#pragma once

class UTimeManager
{
public:
	void Initialize();
	void Update();

	inline float DeltaTime() { return DeltaTimeValue; }

private:
	LARGE_INTEGER CpuFrequency = {};
	LARGE_INTEGER PrevFrequency = {};
	LARGE_INTEGER CurrentFrequency = {};
	float DeltaTimeValue = 0;
};

