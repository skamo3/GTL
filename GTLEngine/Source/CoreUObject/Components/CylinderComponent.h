#pragma once

#include "PrimitiveComponent.h"

class UCylinderComponent: public UPrimitiveComponent
{
	DECLARE_CLASS(UCylinderComponent, UPrimitiveComponent)
public:
	UCylinderComponent();
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;
};