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
	return FAABB(FVector(FLT_MAX, FLT_MAX, FLT_MAX), FVector(FLT_MIN, FLT_MIN, FLT_MIN));
}

bool UActorComponent::IsIntersect(FRay ray, float hitDistance, FVector& hitPoint) const {
	return false;
}
