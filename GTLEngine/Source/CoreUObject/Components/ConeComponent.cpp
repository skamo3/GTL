#include "pch.h"
#include "ConeComponent.h"

UConeComponent::UConeComponent()
	: UPrimitiveComponent()
{
	PrimitiveType = EPrimitiveType::Cone;
}

void UConeComponent::Tick(float TickTime)
{
}

void UConeComponent::Destroy()
{
}
