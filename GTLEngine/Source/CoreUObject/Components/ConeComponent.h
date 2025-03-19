#pragma once

#include "PrimitiveComponent.h"

class UConeComponent : public UPrimitiveComponent
{
	DECLARE_CLASS(UConeComponent, UPrimitiveComponent)
public:
	UConeComponent();
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;
protected:
};