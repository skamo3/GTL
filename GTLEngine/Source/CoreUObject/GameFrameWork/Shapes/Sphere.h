#pragma once

#include "GameFrameWork/Actor.h"

class USphereComponent;

class ASphere : public AActor
{
public:
	ASphere();

public:
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;

private:
	USphereComponent* SphereComponent;

};