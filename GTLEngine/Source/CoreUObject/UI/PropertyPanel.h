#pragma once

#include "Math/Vector.h"
#include "Gizmo/GizmoManager.h"
#include "UI/UIBase.h"

class UPropertyPanel: public UUIBase
{
public:
	UPropertyPanel();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void Destroy() override;
private:
	void Render();


private:
	float Location[3] = { 0, 0, 0 };
	float Rotation[3] = { 0, 0, 0 };
	float Scale[3] = { 0, 0, 0 };
	int32 UUID;
	
	float WindowWidth;
	float WindowHeight;
	UGizmoManager* gizmoManager;
};
