#include "pch.h"
#include "Cube.h"
#include "Components/CubeComponent.h"

ACube::ACube()
	: AActor()
{
	CubeComponent = AddComponent<UCubeComponent>(this);
	CubeComponent->SetupAttachment(RootComponent);
}

void ACube::Tick(float TickTime)
{
	AActor::Tick(TickTime);
}

void ACube::Destroy()
{
	AActor::Destroy();
}
