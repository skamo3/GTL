#pragma once

#include "GameFrameWork/Actor.h"

class UTriangleComponent;

class ATriangle : public AActor
{
public:
	ATriangle();

public:
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;

private:
	UTriangleComponent* TriangleComponent;

};