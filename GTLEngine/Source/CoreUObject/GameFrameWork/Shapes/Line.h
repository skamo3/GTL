#pragma once

#include "CoreUObject/GameFrameWork/Actor.h"

class ULineComponent;

class ALine: public AActor {
public:
	ALine();
public:
	void SetRay(FRay ray);
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;

private:
	ULineComponent* LineComponent;

};