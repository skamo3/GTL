#include "pch.h"
#include "ActorComponent.h"

void UActorComponent::Tick(float TickTime)
{
	// TODO: Log 추가.
}

void UActorComponent::Destroy()
{
}

FAABB UActorComponent::GetAABB() const {
	return FAABB(FVector(FLT_MAX, FLT_MAX, FLT_MAX), FVector(-FLT_MAX, -FLT_MAX, -FLT_MAX));
}

bool UActorComponent::IsRayIntersect(FRay ray, float hitDistance, FVector& hitPoint) const {
	return false;
}
