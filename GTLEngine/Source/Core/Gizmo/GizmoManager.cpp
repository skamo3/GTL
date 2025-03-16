#include "pch.h"
#include "GizmoManager.h"

#include "Gizmo/GizmoActor.h"
#include "Input/InputManager.h"

#include "Engine.h"
#include "World.h"
#include "GameFrameWork/Camera.h"
#include "GameFrameWork/Actor.h"

#include "DirectXMath.h"
#include "Core/Resource/Types.h"

#include "Utils/Math/Geometry.h"

UGizmoManager::UGizmoManager()
	: SelectedAxis(ESelectedAxis::None), GizmoType(EGizmoType::Translate), GizmoActor(nullptr), SelectedActor(nullptr)
{
	GizmoActor = new AGizmoActor();
}

void UGizmoManager::Tick(float DeltaTime)
{
	UInputManager* InputManager = UEngine::GetEngine().GetInputManager();

	// 마우스 왼쪽 클릭 했을 때
	// Ray를 생성하고 GizmoActor와 교차하는지 확인.
	if (InputManager->GetMouseDown(UInputManager::EMouseButton::LEFT))
	{
		SelectedAxis = ESelectedAxis::None;

		float MouseDeltaX = static_cast<float>(InputManager->GetMouseDeltaX());
		float MouseDeltaY = static_cast<float>(InputManager->GetMouseDeltaY());
		

	}


}

void UGizmoManager::Destroy()
{
}

IClickable* UGizmoManager::PickClickable(float MouseX, float MouseY) const {
	FRay ray = Geometry::CreateRayWithMouse(MouseX, MouseY);
	AActor* camera = UEngine::GetEngine().GetWorld()->GetCamera();
	TArray<IClickable*> clickables = IClickable::GetClickableList();
	IClickable* selected = nullptr;
	TArray<IClickable*> selectedList = TArray<IClickable*>();
	

	float minDistancePow = FLT_MAX;
	FVector hitpoint;
	for (IClickable* clickable: clickables) {
		if ( clickable->IsClicked(ray, 100.f, hitpoint) &&
			minDistancePow > (camera->GetActorLocation() - hitpoint).LengthSquared()
			) {
			minDistancePow = (camera->GetActorLocation() - hitpoint).LengthSquared();
			selected = clickable;
		}
	}
	return selected;
}

bool UGizmoManager::IsRayIntersect(UActorComponent* comp, FRay ray, float maxDistance) const {


	return false;
}
