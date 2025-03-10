#pragma once

#include "Math/Vector.h"
#include "UI/UIBase.h"

class UJunglePropertyWindow: public UUIBase
{
public:
	explicit UJunglePropertyWindow(UUIManager* InUIManager);
	void Destroy() override;

private:
	FVector objectTranslation = { -0.140f, 0.030f, 0.0f };
	FVector objectRotation = { 0.0f, 0.0f, 0.0f };
	FVector objectScale = { 1.0f, 1.0f, 1.0f };

private:
	void Draw() override;
	void DrawObjectTranslation();
	void DrawObjectRotation();
	void DrawObjectScale();
};
