#pragma once

#include "PrimitiveComponent.h"

class UCubeComponent : public UPrimitiveComponent
{
public:
	UCubeComponent()
		: UPrimitiveComponent()
	{
		PrimitiveType = EPrimitiveType::Cube;
	}

	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;
};