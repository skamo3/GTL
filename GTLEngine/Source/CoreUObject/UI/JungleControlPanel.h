#pragma once

#include "Math/Vector.h"

#include "UI/UIManager.h"

const char* primitives[] = { "Sphere", "Cube", "Triangle" };

class UUIManager;

class UJungleControlPanel 
{
public:
	UJungleControlPanel();
	~UJungleControlPanel();

private:
	UUIManager* UIManager;

private:
	int currentPrimitive = 0;
	int spawnNum = 1;
	char sceneName[128] = "Default";
	float fovValue = 53.f;
	FVector cameraLocation = { -1.037f, 0.716f, 0.330f };
	FVector cameraRotation = { 0.680f, 1.970f, 0.000f };

	char* strOut;
	size_t bufSize;

	void Draw();
	template<typename T>
	void ChangeNumToStrWithMargin(int marginNum, T num);
};

template<typename T>
void UJungleControlPanel::ChangeNumToStrWithMargin(int marginNum, T num)
{
	bufSize = UIManager->ChangeNumToStrWithMargin(4, num).size() + 1;
	//strOut = new char[bufSize];
	//std::strncpy(strOut, UIManager.ChangeNumToStrWithMargin(4, num).c_str(), bufSize);
	//strOut[bufSize - 1] = '\0';
}