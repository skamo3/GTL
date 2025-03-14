#include "pch.h"
#include "CameraComponent.h"

UCameraComponent::UCameraComponent()
	: FieldOfView(60.f), NearClip(0.1f), FarClip(1000.f)
{
}

void UCameraComponent::Tick(float TickTime)
{
	UActorComponent::Tick(TickTime);
	// TODO: Log 추가.
}

void UCameraComponent::Destroy()
{
	USceneComponent::Destroy();
}
