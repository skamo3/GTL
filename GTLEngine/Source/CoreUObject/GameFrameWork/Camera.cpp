#include "pch.h"
#include "Camera.h"

#include "Components/CameraComponent.h"

ACamera::ACamera()
{
	CameraComponent = AddComponent<UCameraComponent>(this);
	CameraComponent->SetupAttachment(RootComponent);
}

void ACamera::Tick(float TickTime)
{
}

void ACamera::Destroy()
{
}
