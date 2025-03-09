#pragma once

#include "Math/Vector.h"

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

	char* strOut;
	size_t bufSize;

private:
	void Draw();
	template<typename T>
	void ChangeNumToStrWithMargin(int marginNum, T num);
};