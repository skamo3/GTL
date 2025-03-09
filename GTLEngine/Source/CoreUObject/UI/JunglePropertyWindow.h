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

	char* strOut;
	size_t bufSize;

private:
	void Draw();
	template<typename T>
	void ChangeNumToStrWithMargin(int marginNum, T num);
};

template<typename T>
void UJunglePropertyWindow::ChangeNumToStrWithMargin(int marginNum, T num) {
	bufSize = UIManager->ChangeNumToStrWithMargin(4, num).size() + 1;
	//strOut = new char[bufSize];
	//std::strncpy(strOut, UIManager.ChangeNumToStrWithMargin(4, num).c_str(), bufSize);
	//strOut[bufSize - 1] = '\0';
}