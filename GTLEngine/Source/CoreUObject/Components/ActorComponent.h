#pragma once

#include "Object.h"

class UActorComponent : public UObject
{

public:
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;

public:
};