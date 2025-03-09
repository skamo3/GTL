#pragma once

#include "CoreUObject/Object.h"

class AActor : public UObject
{

public:
	virtual void Init() override;
	virtual void Update(float TickTime) override;
	virtual void Destroy() override;
};
