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

	SetActorRotation(GetActorRotation().Add(0.f, 0.f, 0.1f));
}

void ASphere::Destroy()
{
	AActor::Destroy();
}
