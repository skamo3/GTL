#pragma once

#include "Math/Vector.h"
#include "UI/UIBase.h"

static const char* Items[] = {  "None", "Line", "Plane", "Sphere", "Cube", "Cylinder", "Cone" };

class UControlPanel: public UUIBase
{
public:
	UControlPanel();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void Destroy() override;

private:
	void DrawFPS();
	void DrawSpawnPrimitive();

private:
	int CurrentPrimitiveType;
	uint SpawnNum;
	float Location[3];

};
