#pragma once
#include "CoreUObject/GameFrameWork/Actor.h"

class UGridComponent;

class AGrid : public AActor {
public:
	AGrid();
public:
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;
private:
	UGridComponent* GridComponent;
};

