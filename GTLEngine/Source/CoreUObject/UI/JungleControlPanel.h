#pragma once
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#include "Utils/Math/Vector.h"
#include "Manager/UIManager.h"

const char* primitives[] = { "Sphere", "Cube", "Triangle" };

class UJungleControlPanel 
{
public:
	UJungleControlPanel();
	~UJungleControlPanel();

private:
	UUIManager uUIManager;

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
