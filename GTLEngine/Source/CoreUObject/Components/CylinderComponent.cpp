#include "pch.h"
#include "CylinderComponent.h"

UCylinderComponent::UCylinderComponent()
	: UPrimitiveComponent()
{
	PrimitiveType = EPrimitiveType::Cylinder;
}

void UCylinderComponent::Tick(float TickTime)
{
}

void UCylinderComponent::Destroy()
{
}
