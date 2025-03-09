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
	int fps = 7777;
	int deltaTime = 1;
	int currentPrimitive = 0;
	int spawnNum = 1;
	char sceneName[128] = "Default";
	float fovValue = 53.f;
	FVector cameraLocation = { -1.037f, 0.716f, 0.330f };
	FVector cameraRotation = { 0.680f, 1.970f, 0.000f };


	void Draw();
	void DrawFPS();
	void DrawSpawnPrimitive();
	void DrawSceneManage();
	void DrawCameraSetting();
};
