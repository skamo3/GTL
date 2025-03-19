#include "pch.h"
#include "GizmoArrow.h"

#include "Core/Engine/Engine.h"
#include "CoreUObject/World.h"
#include "Utils/Math/Geometry.h"

UGizmoArrow::UGizmoArrow() : UGizmoBase() {}

void UGizmoArrow::Init(EAxis axis, AActor* Target) {
	UGizmoBase::Init(axis, Target);
	switch ( axis ) {
	case EAxis::X:
		OriginalAABB[0] = FVector(0.f, -0.5f, -0.5f);
		OriginalAABB[1] = FVector(0.f, -0.5f, 0.5f);
		OriginalAABB[2] = FVector(0.f, 0.5f, 0.5f);
		OriginalAABB[3] = FVector(0.f, 0.5f, -0.5f);
		OriginalAABB[4] = FVector(10.f, -0.5f, -0.5f);
		OriginalAABB[5] = FVector(10.f, -0.5f, 0.5f);
		OriginalAABB[6] = FVector(10.f, 0.5f, 0.5f);
		OriginalAABB[7] = FVector(10.f, 0.5f, -0.5f);
		break;
	case EAxis::Y:
		OriginalAABB[0] = FVector(-0.5f, 0.f, -0.5f);
		OriginalAABB[1] = FVector(-0.5f, 0.f, 0.5f);
		OriginalAABB[2] = FVector(0.5f, 0.f, 0.5f);
		OriginalAABB[3] = FVector(0.5f, 0.f, -0.5f);
		OriginalAABB[4] = FVector(-0.5f, 10.f, -0.5f);
		OriginalAABB[5] = FVector(-0.5f, 10.f, 0.5f);
		OriginalAABB[6] = FVector(0.5f, 10.f, 0.5f);
		OriginalAABB[7] = FVector(0.5f, 10.f, -0.5f);
		break;
	case EAxis::Z:
		OriginalAABB[0] = FVector(0.5f, -0.5f, 0.f);
		OriginalAABB[1] = FVector(-0.5f, -0.5f, 0.f);
		OriginalAABB[2] = FVector(-0.5f, 0.5f, 0.f);
		OriginalAABB[3] = FVector(0.5f, 0.5f, 0.f);
		OriginalAABB[4] = FVector(0.5f, -0.5f, 10.f);
		OriginalAABB[5] = FVector(-0.5f, -0.5f, 10.f);
		OriginalAABB[6] = FVector(-0.5f, 0.5f, 10.f);
		OriginalAABB[7] = FVector(0.5f, 0.5f, 10.f);
		break;
	}
}

void UGizmoArrow::Tick(float TickTime) {
	UGizmoBase::Tick(TickTime);
}

void UGizmoArrow::Destroy() {
	UGizmoBase::Destroy();
}

void UGizmoArrow::OnDragTick(int dmx, int dmy) {
	const float sensitive = 20.f;
	FVector orgDir;
	switch(axis) {
	case EAxis::X:
		orgDir = FVector(1, 0, 0);
		break;
	case EAxis::Y:
		orgDir = FVector(0, 1, 0);
		break;
	case EAxis::Z:
		orgDir = FVector(0, 0, 1);
		break;
	}
	
	FMatrix view = UEngine::GetEngine().GetWorld()->GetViewMatrix();
	FMatrix proj = UEngine::GetEngine().GetWorld()->GetProjectionMatrix();
	FVector directionInScreen = (mat * view * proj).TransformDirectionVector(orgDir);
	float dx = dmx / static_cast<float>(UEngine::GetEngine().GetWindowInfo().Width);
	float dy = - dmy / static_cast<float>(UEngine::GetEngine().GetWindowInfo().Height);
	float movement = FVector(dx, dy, 0).Dot(directionInScreen);
	/*OutputDebugString((
		L"(" + std::to_wstring(directionInScreen.GetSafeNormal().X) +
		L"," + std::to_wstring(directionInScreen.GetSafeNormal().Y) +
		L"," + std::to_wstring(directionInScreen.GetSafeNormal().Z) + L")\n"
	).c_str());*/
	FVector newPos = mat.TransformDirectionVector(orgDir) * movement * sensitive + Target->GetActorLocation();
	Target->SetActorLocation(newPos);
}

void UGizmoArrow::OnClick(int mx, int my) {
	startMouseX = mx;
	startMouseY = my;
}

void UGizmoArrow::OnRelease(int mx, int my) {}

bool UGizmoArrow::IsClicked(FRay ray, float maxDistance, FVector& hitpoint) {
	return Geometry::IsRayIntersectAABB(GetAABB(), ray, maxDistance);
}
