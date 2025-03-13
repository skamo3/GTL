#pragma once

#include "Components/PrimitiveComponent.h"

class UGizmoBaseComponent : public UPrimitiveComponent
{
public:
	UGizmoBaseComponent();

	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;


};