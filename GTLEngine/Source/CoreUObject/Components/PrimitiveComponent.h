#pragma once

#include "SceneComponent.h"
#include "Core/Resource/Types.h"

class UPrimitiveComponent : public USceneComponent
{
public:
	UPrimitiveComponent();

	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;

public:
	EPrimitiveType GetPrimitiveType() const { return PrimitiveType; }
	FMatrix GetWorldMatrix() const;

protected:
	EPrimitiveType PrimitiveType;
	bool IsRayIntersectWithTriangle(const FRay& ray, const FVector& v0, const FVector& v1, const FVector& v2, float hitDistance, FVector& hitpoint) const;
};