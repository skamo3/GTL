#pragma once

#include "Components/SceneComponent.h"

class UCameraComponent : public USceneComponent
{

public:
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;

public:
};