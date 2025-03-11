#pragma once

#include "PrimitiveComponent.h"

class USphereComponent : public UPrimitiveComponent
{
public:
	USphereComponent()
		: UPrimitiveComponent()
	{
		PrimitiveType = EPrimitiveType::Sphere;
	}
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;
};