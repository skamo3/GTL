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
	FVector min = FVector(FLT_MAX, FLT_MAX, FLT_MAX);
	FVector max = FVector(FLT_MIN, FLT_MIN, FLT_MIN);

	FVector vecs[8] = {
		FVector(-0.5f, -0.5f, -0.5f),
		FVector(0.5f, -0.5f, -0.5f),
		FVector(-0.5f, 0.5f, -0.5f),
		FVector(0.5f, 0.5f, -0.5f),
		FVector(-0.5f, -0.5f, 0.5f),
		FVector(0.5f, -0.5f, 0.5f),
		FVector(-0.5f, 0.5f, 0.5f),
		FVector(0.5f, 0.5f, 0.5f),
	};

	FMatrix transform = GetWorldMatrix();
	for ( int i = 0; i < 8; i++ ) {
		vecs[i] = transform.TransformVector(vecs[i]);
		if ( vecs[i].X < min.X ) min.X = vecs[i].X;
		if ( vecs[i].Y < min.Y ) min.Y = vecs[i].Y;
		if ( vecs[i].Z < min.Z ) min.Z = vecs[i].Z;
		if ( vecs[i].X > max.X ) max.X = vecs[i].X;
		if ( vecs[i].Y > max.Y ) max.Y = vecs[i].Y;
		if ( vecs[i].Z > max.Z ) max.Z = vecs[i].Z;
	}
	
	return FAABB(min, max);
}
