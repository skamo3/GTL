#pragma once

#include "SceneComponent.h"
#include "Core/Resource/Types.h"

class UPrimitiveComponent : public USceneComponent
{
public:
	UPrimitiveComponent();

	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;
	FMatrix GetWorldMatrix() const override;

public:
	EPrimitiveType GetPrimitiveType() const { return PrimitiveType; }
	virtual FAABB GetAABB() const override;
	virtual bool IsRayIntersect(FRay ray, float hitDistance, FVector& hitPoint) const override;
protected:
	EPrimitiveType PrimitiveType;
	FVector OriginalAABB[8] = {
		FVector(-0.5f, -0.5f, -0.5f),
		FVector(0.5f, -0.5f, -0.5f),
		FVector(-0.5f, 0.5f, -0.5f),
		FVector(0.5f, 0.5f, -0.5f),
		FVector(-0.5f, -0.5f, 0.5f),
		FVector(0.5f, -0.5f, 0.5f),
		FVector(-0.5f, 0.5f, 0.5f),
		FVector(0.5f, 0.5f, 0.5f),
	};
};