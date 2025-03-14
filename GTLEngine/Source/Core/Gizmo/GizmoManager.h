#pragma once

#include "Object.h"

#include "Gizmo/GizmoActor.h"

enum class ESelectedAxis : uint8
{
	None = 0,
	X = 1,
	Y = 2,
	Z = 3
};

enum class EGizmoType : uint8
{
	Translate = 0,
	Rotate = 1,
	Scale = 2
};

class UGizmoManager : public UObject
{

public:
	UGizmoManager();

	virtual void Tick(float DeltaTime) override;
	virtual void Destroy() override;

public:
	ESelectedAxis GetESelectedAxis() const { return SelectedAxis; }
	EGizmoType GetGizmoType() const { return GizmoType; }

private:
	ESelectedAxis SelectedAxis;
	EGizmoType GizmoType;

	AGizmoActor* GizmoActor;
	AActor* SelectedActor;

	void RayCast2Dto3D(float MouseX, float MouseY);

};

