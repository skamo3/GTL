#include "pch.h"
#include "CameraComponent.h"

void UCameraComponent::Tick(float TickTime)
{
	UActorComponent::Tick(TickTime);
	// TODO: Log 추가.
}

void UCameraComponent::Destroy()
{
	USceneComponent::Destroy();
}
