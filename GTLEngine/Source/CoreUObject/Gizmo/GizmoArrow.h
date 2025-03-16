#pragma once

#include "GizmoBase.h"

class UGizmoArrow : public UGizmoBase
{

public:
	UGizmoArrow(EAxis axis, AActor* Target);

	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;

	void OnClick(int mx, int my) override;
	void OnDragTick(int dmx, int dmy) override;
	void OnRelease(int mx, int my) override;

	virtual bool IsClicked(FRay ray, float maxDistance, FVector& hitpoint) override;
};