#pragma once
#include "PrimitiveComponent.h"
class UGridComponent :public UPrimitiveComponent {
public:
	UGridComponent();

	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;
};

