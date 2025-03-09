#pragma once

#include "CoreUObject/Object.h"

class USceneComponent;
	
class AActor : public UObject
{
public:
	AActor();


public:
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;

public:
	USceneComponent* GetRootComponent() const { return RootComponent; }

private:
	USceneComponent* RootComponent;

};
