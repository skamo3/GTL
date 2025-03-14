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

struct FRay;

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

	FRay CreateRayWithMouse(float MouseX, float MouseY);
	bool IsRayItersectAABB(FAABB aabb, FRay ray, float maxDistance) const;

public:
	void PickActor(float MouseX, float MouseY);
};

