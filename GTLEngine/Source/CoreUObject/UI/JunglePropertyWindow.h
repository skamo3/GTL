#pragma once

#include "Math/Vector.h"

#include "UI/UIManager.h"

class UUIManager;

class UJunglePropertyWindow {
public:
	UJunglePropertyWindow();
	~UJunglePropertyWindow();

private:
	UUIManager* UIManager;

private:
	FVector objectTranslation = { -0.140f, 0.030f, 0.0f };
	FVector objectRotation = { 0.0f, 0.0f, 0.0f };
	FVector objectScale = { 1.0f, 1.0f, 1.0f };

private:
	void Draw();
	void DrawObjectTranslation();
	void DrawObjectRotation();
	void DrawObjectScale();
};
