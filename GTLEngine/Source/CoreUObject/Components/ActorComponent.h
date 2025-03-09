#pragma once

#include "Object.h"

class AActor;

class UActorComponent : public UObject
{

public:
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;

public:
	AActor* GetOwner() const { return OwnerPrivate; }

private:
	AActor* OwnerPrivate;
};