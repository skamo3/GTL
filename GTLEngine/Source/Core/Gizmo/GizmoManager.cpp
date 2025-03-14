#include "pch.h"
#include "GizmoManager.h"

#include "Gizmo/GizmoActor.h"
#include "Input/InputManager.h"

#include "Engine.h"
#include "World.h"
#include "GameFrameWork/Camera.h"
#include "GameFrameWork/Actor.h"

#include "DirectXMath.h"

UGizmoManager::UGizmoManager()
	: SelectedAxis(ESelectedAxis::None), GizmoType(EGizmoType::Translate), GizmoActor(nullptr)
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

void UGizmoManager::RayCast2Dto3D(float MouseX, float MouseY)
{
	FWindowInfo WInfo = UEngine::GetEngine().GetWindowInfo();

	float ViewX = (2.0f * MouseX) / WInfo.Width - 1.0f;
	float ViewY = (-2.0f * MouseY) / WInfo.Height;

	// Projection 공간으로 변환
	FVector4 RayOrigin = FVector4(ViewX, ViewY, 0.0f, 1.0f);
	FVector4 RayEnd = FVector4(ViewX, ViewY, 1.0f, 1.0f);

	// View 공간으로 변환
	FMatrix InvProjMat = UEngine::GetEngine().GetWorld()->GetProjectionMatrix().Inverse();

	ACamera* Camera = UEngine::GetEngine().GetWorld()->GetCamera();

	RayOrigin = InvProjMat.TransformVector4(RayOrigin);
	RayOrigin.W = 1.0f;
	RayEnd = InvProjMat.TransformVector4(RayEnd);
	RayEnd *= 1000.0f;
	RayEnd.W = 1.0f;

	FMatrix InvViewMat = UEngine::GetEngine().GetWorld()->GetViewMatrix().Inverse();
	RayOrigin = InvViewMat.TransformVector4(RayOrigin);
	RayOrigin /= RayOrigin.W = 1.0f;
	RayEnd = InvViewMat.TransformVector4(RayEnd);
	RayEnd /= RayEnd.W = 1.0f;

	// Ray 생성.
	FVector RayDir = (RayEnd - RayOrigin).GetSafeNormal();

	// Picking 로직 구현.


	// or
	
	// 기즈모 이동.
	float Distance = FVector::Distance(RayOrigin, SelectedActor->GetActorLocation());
	


	// 현재 카메라의 MVP 정보.
}
