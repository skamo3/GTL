#pragma once

#include "GameFrameWork/Actor.h"

class UPlaneComponent;

class APlane : public AActor
{
public:
	APlane();

public:
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;

private:
	UPlaneComponent* PlaneComponent;

};