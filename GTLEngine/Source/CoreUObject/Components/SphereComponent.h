#pragma once

#include "PrimitiveComponent.h"

class USphereComponent : public UPrimitiveComponent
{
public:
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;
};