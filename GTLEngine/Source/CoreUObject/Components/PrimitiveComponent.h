#pragma once

#include "SceneComponent.h"

class UPrimitiveComponent : public USceneComponent
{
public:
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;
};