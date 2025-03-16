#include "pch.h"
#include "GizmoArrow.h"

#include "Core/Engine/Engine.h"
#include "CoreUObject/World.h"

UGizmoArrow::UGizmoArrow(EAxis axis, AActor* Target): UGizmoBase(axis, Target) {}

void UGizmoArrow::Tick(float TickTime) {
	UGizmoBase::Tick(TickTime);
}

void UGizmoArrow::Destroy() {
	UGizmoBase::Destroy();
}

void UGizmoArrow::OnDragTick(int dmx, int dmy) {
	const float sensitive = 20.f;
	FVector front = mat.TransformDirectionVector(FVector(1, 0, 0));
	FMatrix view = UEngine::GetEngine().GetWorld()->GetViewMatrix();
	FMatrix proj = UEngine::GetEngine().GetWorld()->GetProjectionMatrix();
	FVector directionInScreen = (view * proj).TransformDirectionVector(front);
	float dx = dmx / static_cast<float>(UEngine::GetEngine().GetWindowInfo().Width);
	float dy = dmy / static_cast<float>(UEngine::GetEngine().GetWindowInfo().Height);
	float movement = FVector(dx, dy, 0).Dot(directionInScreen);
	
	FVector newPos = front * movement * sensitive + Target->GetActorLocation();
	Target->SetActorLocation(newPos);
}

void UGizmoArrow::OnClick(int mx, int my) {
	startMouseX = mx;
	startMouseY = my;
}

void UGizmoArrow::OnRelease(int mx, int my) {}