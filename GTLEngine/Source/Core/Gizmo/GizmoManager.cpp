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

#include <algorithm>

using std::max;
using std::min;

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

FRay UGizmoManager::CreateRayWithMouse(float MouseX, float MouseY) const
{
	FWindowInfo WInfo = UEngine::GetEngine().GetWindowInfo();

	//float ViewX = (2.0f * MouseX) / WInfo.Width - 1.0f;
	//float ViewY = (-2.0f * MouseY) / WInfo.Height + 1.0f;
	float NDCX = MouseX;
	float NDCY = MouseY;

	// Projection 공간으로 변환
	FVector4 RayOrigin = FVector4(NDCX, NDCY, 0.0f, 1.0f);
	FVector4 RayEnd = FVector4(NDCX, NDCY, 1.0f, 1.0f);

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

	return FRay(RayOrigin, RayDir);
	// Picking 로직 구현.


	// or
	
	// 기즈모 이동.
	// float Distance = FVector::Distance(RayOrigin, SelectedActor->GetActorLocation());
	


	// 현재 카메라의 MVP 정보.
}

AActor* UGizmoManager::PickActor(float MouseX, float MouseY) const {
	FRay ray = CreateRayWithMouse(MouseX, MouseY);
	TArray<AActor*> actors = UEngine::GetEngine().GetWorld()->GetActors();
	AActor* camera = UEngine::GetEngine().GetWorld()->GetCamera();
	AActor* selected = nullptr;
	TArray<AActor*> selectedList = TArray<AActor*>();
	float minDistancePow = FLT_MAX;

	// aabb로 1차 검사
	for (AActor* actor: actors) {
		FAABB aabb = actor->GetAABB();
		if ( IsRayIntersectAABB(aabb, ray, 100.f) ) {
			selectedList.push_back(actor);
		}
	}

	// moller-trumbore algorithm으로 2차 검사
	for (AActor* actor: selectedList) {
		for (UActorComponent* comp: actor->GetOwnedComponent()) {
			FVector hitpoint;
			if (comp->IsIntersect(ray, 100.f, hitpoint) && 
				minDistancePow > (camera->GetActorLocation() - hitpoint).LengthSquared()
			) {
				minDistancePow = (camera->GetActorLocation() - hitpoint).LengthSquared();
				selected = actor;
			}
		}
	}
	
	return selected;
}

bool UGizmoManager::IsRayIntersectAABB(FAABB aabb, FRay ray, float maxDistance = 100.f) const {

	// reference: https://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms
	FVector dirfrac(1 / ray.Direction.X, 1 / ray.Direction.Y, 1 / ray.Direction.Z);

	float t1 = (aabb.min.X - ray.Origin.X) * dirfrac.X;
	float t2 = (aabb.max.X - ray.Origin.X) * dirfrac.X;
	float t3 = (aabb.min.Y - ray.Origin.Y) * dirfrac.Y;
	float t4 = (aabb.max.Y - ray.Origin.Y) * dirfrac.Y;
	float t5 = (aabb.min.Z - ray.Origin.Z) * dirfrac.Z;
	float t6 = (aabb.max.Z - ray.Origin.Z) * dirfrac.Z;

	float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
	float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if ( tmax < 0 ) {
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if ( tmin > tmax ) {
		return false;
	}

	return true;
}

bool UGizmoManager::IsRayIntersect(UActorComponent* comp, FRay ray, float maxDistance) const {


	return false;
}
