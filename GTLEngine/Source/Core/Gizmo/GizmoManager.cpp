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

#include "CoreUObject/Gizmo/GizmoArrow.h"

UGizmoManager::UGizmoManager()
	: GizmoType(EGizmoType::Translate), SelectedActor(nullptr), Gizmo()
{
}

void UGizmoManager::Tick(float DeltaTime)
{
	UInputManager* InputManager = UEngine::GetEngine().GetInputManager();
	for ( auto& g : Gizmo )
		g->Tick(DeltaTime);

	Picking();
}

void UGizmoManager::Destroy()
{
}

void UGizmoManager::Picking() {
	UInputManager* inputManager = UEngine::GetEngine().GetInputManager();


	if ( inputManager->GetMouseDown(UInputManager::EMouseButton::LEFT) ) {
		FWindowInfo winInfo = UEngine::GetEngine().GetWindowInfo();
		// test pick
		float mouse_x = inputManager->GetMouseNdcX();
		float mouse_y = inputManager->GetMouseNdcY();
		IClickable* picked = PickClickable(mouse_x, mouse_y);

		IDragable* pickedDragable;
		if ( picked && (pickedDragable = dynamic_cast<IDragable*>(picked)) ) {
			DragTarget = pickedDragable;
		}

		// if gizmo picked
		UGizmoBase* pickedGizmo;
		if ( picked && (pickedGizmo = dynamic_cast<UGizmoBase*>(picked)) ) {
			return;
		}


		// release pick
		for ( auto& clickable : IClickable::GetClickableList() ) {
			clickable->OnRelease(mouse_x, mouse_y);
		}
		ClearSelected();


		// if actor picked
		AActor* pickedActor;
		if ( picked && (pickedActor = dynamic_cast<AActor*>(picked)) ) {
			picked->OnClick(mouse_x, mouse_y);
			SelectedActor = pickedActor;

			// pick gizmo
			switch ( Mode ) {
			case EGizmoType::Translate:
				Gizmo.push_back(new UGizmoArrow(UGizmoBase::EAxis::X, pickedActor));
				Gizmo.push_back(new UGizmoArrow(UGizmoBase::EAxis::Y, pickedActor));
				Gizmo.push_back(new UGizmoArrow(UGizmoBase::EAxis::Z, pickedActor));
				break;
			case EGizmoType::Rotate:
			case EGizmoType::Scale:
				break;
			}
			return;
		}
	} else if ( inputManager->GetMouseUp(UInputManager::EMouseButton::LEFT) ) {
		DragTarget = nullptr;

	} else if ( inputManager->GetMouseButton(UInputManager::EMouseButton::LEFT) ) {
		if ( DragTarget ) {
			int mouse_dx = inputManager->GetMouseDeltaX();
			int mouse_dy = inputManager->GetMouseDeltaY();
			DragTarget->OnDragTick(mouse_dx, mouse_dy);
		}
	}
}


IClickable* UGizmoManager::PickClickable(float MouseX, float MouseY) const {
	FRay ray = Geometry::CreateRayWithMouse(MouseX, MouseY);
	AActor* camera = UEngine::GetEngine().GetWorld()->GetCamera();
	TList<IClickable*> clickables = IClickable::GetClickableList();
	IClickable* selected = nullptr;

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

void UGizmoManager::ClearSelected() {
	SelectedActor = nullptr;
	for ( auto& g : Gizmo )
		delete g;
	Gizmo.clear();
}

const TArray<UGizmoBase*> UGizmoManager::GetGizmo() {
	return Gizmo;
}
