#pragma once

#include "GizmoBaseComponent.h"

class UGizmoArrowComponent : public UGizmoBaseComponent
{

public:
	UGizmoArrowComponent();

	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;


};