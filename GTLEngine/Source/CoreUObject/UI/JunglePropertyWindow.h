#pragma once

#include "UI/UIBase.h"

class UJunglePropertyWindow: public UUIBase
{
public:
	explicit UJunglePropertyWindow(UUIManager* InUIManager);
	void Destroy() override;

private:
	void Draw() override;
	void DrawObjectTranslation();
	void DrawObjectRotation();
	void DrawObjectScale();
};
