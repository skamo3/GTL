#include "pch.h"
#include "PlaneComponent.h"

UPlaneComponent::UPlaneComponent()
	: UPrimitiveComponent()
{
	PrimitiveType = EPrimitiveType::Plane;
}

void UPlaneComponent::Tick(float TickTime)
{
}

void UPlaneComponent::Destroy()
{
}
