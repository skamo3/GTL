#pragma once

#include "Object.h"

#include "Gizmo/GizmoBase.h"

enum class EGizmoType : uint8
{
	Translate = 0,
	Rotate = 1,
	Scale = 2
};

struct FRay;

class UGizmoManager
{

public:
	UGizmoManager();

	void Tick(float DeltaTime);
	void Destroy();

	void Picking();
	EGizmoType GetGizmoType() const { return GizmoType; }


private:
	EGizmoType GizmoType;
	AActor* SelectedActor;
	IDragable* DragTarget;
	TArray<UGizmoBase*> Gizmo;
	EGizmoType Mode = EGizmoType::Rotate;
public:
	IClickable* PickClickable(float MouseX, float MouseY) const;
	void ClearSelected();
	const TArray<UGizmoBase*> GetGizmo();
	inline AActor* GetSelected() const { return SelectedActor; }
};

