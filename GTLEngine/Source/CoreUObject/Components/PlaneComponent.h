#pragma once

#include "PrimitiveComponent.h"

class UPlaneComponent : public UPrimitiveComponent
{
public:
	UPlaneComponent();
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;
	virtual FAABB GetAABB() override;
};