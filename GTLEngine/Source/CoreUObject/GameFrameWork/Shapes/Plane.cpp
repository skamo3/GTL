#include "pch.h"
#include "Plane.h"
#include "Components/PlaneComponent.h"

APlane::APlane()
	: AActor()
{
	PlaneComponent = AddComponent<UPlaneComponent>(this);
	PlaneComponent->SetupAttachment(RootComponent);
}

void APlane::Tick(float TickTime)
{
	AActor::Tick(TickTime);
}

void APlane::Destroy()
{
	AActor::Destroy();
}
