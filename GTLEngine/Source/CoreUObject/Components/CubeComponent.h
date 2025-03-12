#pragma once

#include "PrimitiveComponent.h"

class UCubeComponent : public UPrimitiveComponent
{
public:
	UCubeComponent();

	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;
};