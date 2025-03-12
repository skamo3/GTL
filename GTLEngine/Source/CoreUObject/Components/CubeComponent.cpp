#include "pch.h"
#include "CubeComponent.h"

#include "Resource/Types.h"

UCubeComponent::UCubeComponent()
	: UPrimitiveComponent()
{
	PrimitiveType = EPrimitiveType::Cube;
}

void UCubeComponent::Tick(float TickTime)
{
}

void UCubeComponent::Destroy()
{
}
