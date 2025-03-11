#include "pch.h"
#include "Camera.h"

#include "Components/CameraComponent.h"
#include "Engine/Engine.h"
#include "Input/InputManager.h"

ACamera::ACamera()
{
	CameraComponent = AddComponent<UCameraComponent>(this);
	CameraComponent->SetupAttachment(RootComponent);
	SetActorLocation(FVector(0, 0, 0));
	SetActorRotation(FVector(0, 0, 0));
	SetActorScale(FVector(1, 1, 1));
}

void ACamera::Tick(float TickTime)
{
	FVector CameraLocation = GetActorLocation();
	FVector CameraRotation = GetActorRotation();

	if (UEngine::GetEngine().GetInputManager()->GetKey('W'))
	{
		CameraLocation += FVector(0, 0, -10) * TickTime;
	}
	if (UEngine::GetEngine().GetInputManager()->GetKey('S'))
	{
		CameraLocation += FVector(0, 0, 10) * TickTime;
	}
	if (UEngine::GetEngine().GetInputManager()->GetKey('A'))
	{
		CameraLocation += FVector(-10, 0, 0) * TickTime;
	}
	if (UEngine::GetEngine().GetInputManager()->GetKey('D'))
	{
		CameraLocation += FVector(10, 0, 0) * TickTime;
	}

	SetActorLocation(CameraLocation);
}

void ACamera::Destroy()
{
}

FMatrix ACamera::GetViewMatrix() const
{
	const FMatrix CameraRotationMatrix = FMath::CreateRotationMatrix(GetActorRotation());
	const FVector CameraLocation = GetActorLocation();
	const FVector CameraUp = FMath::TransformDirection(FVector::UpVector, CameraRotationMatrix);;
	const FVector CameraDir = FMath::TransformDirection(FVector::RightVector, CameraRotationMatrix);

	return FMath::CreateViewMatrixByDirection(CameraLocation, CameraDir, CameraUp);
}

FMatrix ACamera::GetProjectionMatrix(float width, float height) const
{
	const float AspectRatio = width / height;

	return FMatrix::CreatePerspectiveProjectionMatrixLeftHand(90.f, AspectRatio, 1.f, 1000.f);
}
