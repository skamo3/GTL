#include "pch.h"
#include "PrimitiveComponent.h"

UPrimitiveComponent::UPrimitiveComponent()
	: USceneComponent(), PrimitiveType(EPrimitiveType::None)
{
}

void UPrimitiveComponent::Tick(float TickTime)
{
}

void UPrimitiveComponent::Destroy()
{
}
