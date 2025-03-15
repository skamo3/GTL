#include "pch.h"
#include "TriangleComponent.h"

UTriangleComponent::UTriangleComponent()
	: UPrimitiveComponent()
{
	PrimitiveType = EPrimitiveType::Triangle;
}

void UTriangleComponent::Tick(float TickTime)
{
}

void UTriangleComponent::Destroy()
{
}
