#include "pch.h"
#include "GizmoBaseComponent.h"

UGizmoBaseComponent::UGizmoBaseComponent()
{
}

void UGizmoBaseComponent::Tick(float TickTime)
{
	UPrimitiveComponent::Tick(TickTime);
}

void UGizmoBaseComponent::Destroy()
{
	UPrimitiveComponent::Destroy();
}
