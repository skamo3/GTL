#pragma once

#include "GameFrameWork/Actor.h"

class UCylinderComponent;

class ACylinder : public AActor
{
public:
	ACylinder();

public:
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;

private:
	UCylinderComponent* CylinderComponent;

};