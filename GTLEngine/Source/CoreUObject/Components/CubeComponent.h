#pragma once

#include "PrimitiveComponent.h"

class UCubeComponent : public UPrimitiveComponent
{
public:
	UCubeComponent();

	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;
	virtual FAABB GetAABB() const override;
	virtual bool IsRayIntersect(FRay ray, float hitDistance, FVector& hitPoint) const override;
};