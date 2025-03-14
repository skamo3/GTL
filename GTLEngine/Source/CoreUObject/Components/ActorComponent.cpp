#include "pch.h"
#include "ActorComponent.h"

void UActorComponent::Tick(float TickTime)
{
	// TODO: Log 추가.
}

void UActorComponent::Destroy()
{
}

FAABB UActorComponent::GetAABB() {
	return FAABB(FVector::Zero(), FVector::Zero());
}
