#pragma once

#include "Math/Vector.h"
#include "UI/UIBase.h"

const char* primitives[] = { "Sphere", "Cube", "Triangle" }; // TODO:

class UJungleControlPanel: public UUIBase
{
public:
	explicit UJungleControlPanel(UUIManager* InUIManager);
	void Destroy() override;

private:
	int currentPrimitive = 0;
	int spawnNum = 1;
	char sceneName[128] = "Default";


	void Draw() override;
	void DrawFPS();
	void DrawSpawnPrimitive();
	void DrawSceneManage();
	void DrawCameraSetting();
};
