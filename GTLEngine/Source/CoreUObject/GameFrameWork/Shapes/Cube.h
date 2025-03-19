#pragma once

#include "GameFrameWork/Actor.h"

class UCubeComponent;
class USphereComponent;

class ACube : public AActor
{
public:
	ACube();

public:
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;
private:
	UCubeComponent* CubeComponent;
	UCubeComponent* CubeComponent2;

};