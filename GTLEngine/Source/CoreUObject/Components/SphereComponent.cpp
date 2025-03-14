#include "pch.h"
#include "SphereComponent.h"

USphereComponent::USphereComponent()
	: UPrimitiveComponent()
{
	PrimitiveType = EPrimitiveType::Sphere;
}

void USphereComponent::Tick(float TickTime)
{
}

void USphereComponent::Destroy()
{
}
