#include "pch.h"
#include "CubeComponent.h"

#include "Resource/Types.h"
#include "Engine.h"
#include "Core/Gizmo/GizmoManager.h"
#include "Input/InputManager.h"

UCubeComponent::UCubeComponent()
	: UPrimitiveComponent()
{
	PrimitiveType = EPrimitiveType::Cube;
}

void UCubeComponent::Tick(float TickTime)
{
	UInputManager* inputManager = UEngine::GetEngine().GetInputManager();
	UGizmoManager* gizmoManager = UEngine::GetEngine().GetGizmo();
	if (inputManager->GetMouseDown(UInputManager::EMouseButton::LEFT)) {
		float mouse_x = inputManager->GetMouseNdcX();
		float mouse_y = inputManager->GetMouseNdcY();
		gizmoManager->PickActor(mouse_x, mouse_y);
	}
}

void UCubeComponent::Destroy()
{
}

FAABB UCubeComponent::GetAABB() {
	FVector min = FVector(-0.5f, -0.5f, -0.5f);
	FVector max = FVector(0.5f, 0.5f, 0.5f);

	FVector scale = GetComponentScale();
	FRotator rot = GetComponentRotation();
	FVector pos = GetComponentLocation();
	FMatrix transform = FMatrix::GetScaleMatrix(scale) * FMatrix::GetRotateMatrix(rot) * FMatrix::GetTranslateMatrix(pos);
	min = transform.TransformVector(min);
	max = transform.TransformVector(max);
	return FAABB(min, max);
}
