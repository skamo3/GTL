#pragma once

#include "Components/ActorComponent.h"

class UCameraComponent : public UActorComponent
{

public:
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;

public:
};