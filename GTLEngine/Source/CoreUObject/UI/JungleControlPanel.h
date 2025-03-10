#pragma once

#include "Math/Vector.h"
#include "UI/UIBase.h"

const char* primitives[] = { "Sphere", "Cube", "Triangle" };

class UJungleControlPanel: public UUIBase
{
public:
	explicit UJungleControlPanel(UUIManager* InUIManager);
	void Destroy() override;


private:
	int fps = 7777;
	int deltaTime = 1;
	int currentPrimitive = 0;
	int spawnNum = 1;
	char sceneName[128] = "Default";
	float fovValue = 53.f;
	FVector cameraLocation = { -1.037f, 0.716f, 0.330f };
	FVector cameraRotation = { 0.680f, 1.970f, 0.000f };


	void Draw() override;
	void DrawFPS();
	void DrawSpawnPrimitive();
	void DrawSceneManage();
	void DrawCameraSetting();
};
