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
	//SetActorLocation(GetActorLocation() + FVector(0.0f, 0.1f, 0.0f));
	SetActorRotation(Rotation + FRotator(.0f, 0.0f, 1.0f));
}

void ACube::Destroy()
{
	AActor::Destroy();
}
