#pragma once

#include "GameFrameWork/Actor.h"

class UGizmoArrowComponent;

class AGizmoActor : public AActor
{
public:
	AGizmoActor();

public:
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;

private:
	UGizmoArrowComponent* ArrowComponent;

};
