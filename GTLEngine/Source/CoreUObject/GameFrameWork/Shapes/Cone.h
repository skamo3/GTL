#pragma once

#include "GameFrameWork/Actor.h"

class UConeComponent;

class ACone : public AActor
{
public:
	ACone();

public:
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;

private:
	UConeComponent* ConeComponent;

};