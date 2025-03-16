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

class UGizmoManager : public UObject
{

public:
	UGizmoManager();

	virtual void Tick(float DeltaTime) override;
	virtual void Destroy() override;

	void Picking();
	EGizmoType GetGizmoType() const { return GizmoType; }


private:
	EGizmoType GizmoType;
	AActor* SelectedActor;
	IDragable* DragTarget;
	TArray<UGizmoBase*> Gizmo;
	EGizmoType Mode = EGizmoType::Translate;
public:
	IClickable* PickClickable(float MouseX, float MouseY) const;
	const TArray<UGizmoBase*> GetGizmo();
};

