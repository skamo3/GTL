#pragma once

#include "PrimitiveComponent.h"

class USphereComponent : public UPrimitiveComponent
{
public:
	USphereComponent();

	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;
	virtual FBoundingBox GetAABB() const override;
};