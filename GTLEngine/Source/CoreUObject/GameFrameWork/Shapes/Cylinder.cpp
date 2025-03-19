#include "pch.h"
#include "Cylinder.h"
#include "Components/CylinderComponent.h"

ACylinder::ACylinder()
	: AActor()
{
	CylinderComponent = AddComponent<UCylinderComponent>(this);
	CylinderComponent->SetupAttachment(RootComponent);
}

void ACylinder::Tick(float TickTime)
{
	AActor::Tick(TickTime);
}

void ACylinder::Destroy()
{
	AActor::Destroy();
}