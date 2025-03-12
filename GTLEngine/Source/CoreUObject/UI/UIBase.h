#pragma once
#include "CoreUObject/Object.h"

class UUIManager;

class UUIBase : public UObject
{
public:
	virtual void Tick(float TickTime) = 0;
	virtual void Destroy() = 0;

};