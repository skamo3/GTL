#pragma once
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#include "Utils/Math/Vector.h"
#include "Manager/UIManager.h"

class UJunglePropertyWindow {
public:
	UJunglePropertyWindow();
	~UJunglePropertyWindow();

private:
	UUIManager uUIManager;

private:
	FVector objectTranslation = { -0.140f, 0.030f, 0.0f };
	FVector objectRotation = { 0.0f, 0.0f, 0.0f };
	FVector objectScale = { 1.0f, 1.0f, 1.0f };

	char strOut[32] = "";

private:
	void Draw();
	template<typename T>
	void ChangeNumToStrWithMargin(int marginNum, T num);
};