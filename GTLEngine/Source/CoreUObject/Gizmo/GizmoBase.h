#pragma once

//#include "Components/PrimitiveComponent.h"
#include "Core/Resource/Types.h"
#include "CoreUObject/GameFrameWork/Actor.h"
#include "Core/UI/UIInterface.h"

class UGizmoBase : public UObject, public IDragable
{
	DECLARE_CLASS(UGizmoBase, UObject)
public:
	enum class EAxis {
		X,
		Y,
		Z
	};
	static bool IsAbsoluteCoord;
protected:
	FVector OriginalAABB[8] = {
		FVector(0.f, -0.5f, -0.5f),
		FVector(0.f, -0.5f, -0.5f),
		FVector(0.f, 0.5f, -0.5f),
		FVector(0.f, 0.5f, -0.5f),
		FVector(10.f, -0.5f, 0.5f),
		FVector(10.f, -0.5f, 0.5f),
		FVector(10.f, 0.5f, 0.5f),
		FVector(10.f, 0.5f, 0.5f),
	};

	EAxis axis = EAxis::X;
	AActor* Target;
	int startMouseX, startMouseY;
	FMatrix mat = FMatrix::Identity();
public:
	UGizmoBase();

	void Init(EAxis axis, AActor* Target);

	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;

	virtual FBoundingBox GetAABB() const;

	virtual bool IsClicked(FRay ray, float maxDistance, FVector& hitpoint) override;

};