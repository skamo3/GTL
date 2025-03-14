#pragma once

#include "PrimitiveComponent.h"

class UConeComponent : public UPrimitiveComponent
{
public:
	UConeComponent();
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;
};