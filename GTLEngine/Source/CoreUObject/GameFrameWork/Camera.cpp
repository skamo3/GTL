#include "pch.h"
#include "Camera.h"

#include "Components/CameraComponent.h"
#include "Engine/Engine.h"
#include "Input/InputManager.h"
#include "DirectXMath.h"

using namespace DirectX;

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

	// 현재 카메라 회전을 기준으로 바꿔줘야 함.
	FVector Forward = GetActorRotation();
	FVector ForwardDirection = FMath::TransformDirection(FVector::ForwardVector, FMath::CreateRotationMatrix(CameraRotation));
	FVector RightDirection = FMath::TransformDirection(FVector::RightVector, FMath::CreateRotationMatrix(CameraRotation));
	
	UInputManager* InputManager = UEngine::GetEngine().GetInputManager();
	
	if (InputManager->GetKey('W'))
	{
		CameraLocation += ForwardDirection * 10 * TickTime;
	}
	if (InputManager->GetKey('S'))
	{
		CameraLocation -= ForwardDirection * 10 * TickTime;
	}
	if (InputManager->GetKey('A'))
	{
		CameraLocation -= RightDirection * 10 * TickTime;
	}
	if (InputManager->GetKey('D'))
	{
		CameraLocation += RightDirection * 10 * TickTime;
	}

	if (InputManager->GetMouseButton(UInputManager::EMouseButton::RIGHT))
	{
		float MouseDeltaX = InputManager->GetMouseDeltaX();
		float MouseDeltaY = InputManager->GetMouseDeltaY();

		CameraRotation += FVector(0, MouseDeltaX, MouseDeltaY) * TickTime;
		std::cout << CameraRotation.X << " " << CameraRotation.Y << " " << CameraRotation.Z << std::endl;
	}

	SetActorLocation(CameraLocation);
	SetActorRotation(CameraRotation);
}

void ACamera::Destroy()
{
}

FMatrix ACamera::GetViewMatrix() const
{
	const FVector CameraLocation = GetActorLocation();
	const FVector CameraRotation = GetActorRotation();
	FMatrix rotationMatrix = FMath::CreateRotationMatrix(CameraRotation);
	FVector CameraDir = FMath::TransformDirection(FVector::ForwardVector, rotationMatrix);
	FVector CameraUp = FMath::TransformDirection(FVector::UpVector, rotationMatrix);

	return FMath::CreateViewMatrixByDirection(CameraLocation, CameraDir, CameraUp);
}

FMatrix ACamera::GetProjectionMatrix(float width, float height) const
{
	const float AspectRatio = width / height;

	return FMatrix::CreatePerspectiveProjectionMatrixLeftHand(60.f, AspectRatio, 1.f, 1000.f);
}
