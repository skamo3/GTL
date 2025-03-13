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

	FRotator Rotation = GetActorRotation();
	SetActorRotation(Rotation + FVector(0.0, 0.0, 1.0f));
}

void ACube::Destroy()
{
	AActor::Destroy();
}
