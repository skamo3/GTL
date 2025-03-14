#include "pch.h"
#include "Sphere.h"
#include "Components/SphereComponent.h"

ASphere::ASphere()
	: AActor()
{
	SphereComponent = AddComponent<USphereComponent>(this);
	SphereComponent->SetupAttachment(RootComponent);
}

void ASphere::Tick(float TickTime)
{
	AActor::Tick(TickTime);
}

void ASphere::Destroy()
{
	AActor::Destroy();
}
