#include "pch.h"
#include "Camera.h"

#include "Components/CameraComponent.h"
#include "Engine/Engine.h"
#include "Input/InputManager.h"

#include "Math/MathUtils.h"

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
	FRotator CameraRotation = GetActorRotation();

	// 현재 카메라 회전을 기준으로 바꿔줘야 함.
	FRotator Forward = GetActorRotation();
	// 카메라 기준 Forward, Right, Up Vector 구하기
	
	FVector ForwardDirection = CameraRotation.TransformRotVecToMatrix(FVector::ForwardVector);
	FVector RightDirection = CameraRotation.TransformRotVecToMatrix(FVector::RightVector);
	
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
		float MouseDeltaX = static_cast<float>(InputManager->GetMouseDeltaX());
		float MouseDeltaY = static_cast<float>(InputManager->GetMouseDeltaY());

		// Pitch, Yaw, Roll == Y, Z, X
		// TODO: 회전 시 Roll 회전이 적용되는 문제가 생김. Rotator 문제일 수도 있음.
		CameraRotation.Pitch += MouseDeltaY * 5 * TickTime;
		CameraRotation.Yaw -= MouseDeltaX * 5 * TickTime;
		CameraRotation.Roll = 0;
	}

	SetActorLocation(CameraLocation);
	SetActorRotation(CameraRotation);
}

void ACamera::Destroy()
{
}

float ACamera::GetFieldOfView() const
{
	if (!CameraComponent)
		return 0.0f;
	return CameraComponent->GetFieldOfView();
}

float ACamera::GetNearClip() const
{
	if (!CameraComponent)
		return 0.0f;
	return CameraComponent->GetNearClip();
}

float ACamera::GetFarClip() const
{
	if (!CameraComponent)
		return 0.0f;
	return CameraComponent->GetFarClip();
}
