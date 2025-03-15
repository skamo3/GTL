#pragma once

#include "SceneComponent.h"
#include "Core/Resource/Types.h"

class UPrimitiveComponent : public USceneComponent
{
public:
	UPrimitiveComponent();

	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;

public:
	EPrimitiveType GetPrimitiveType() const { return PrimitiveType; }

	virtual FMatrix GetWorldMatrix() const;

protected:
	EPrimitiveType PrimitiveType;
};