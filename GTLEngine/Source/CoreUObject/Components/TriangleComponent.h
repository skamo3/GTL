#pragma once

#include "PrimitiveComponent.h"

class UTriangleComponent : public UPrimitiveComponent
{
	DECLARE_CLASS(UTriangleComponent, UPrimitiveComponent)
public:
	UTriangleComponent();
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;
};