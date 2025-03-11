#pragma once

#include "PrimitiveComponent.h"

class UPlaneComponent : public UPrimitiveComponent
{
public:
	UPlaneComponent()
		: UPrimitiveComponent()
	{
		PrimitiveType = EPrimitiveType::Plane;
	}
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;
};