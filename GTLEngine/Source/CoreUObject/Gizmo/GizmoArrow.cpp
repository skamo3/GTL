#include "pch.h"
#include "GizmoArrow.h"


UGizmoArrow::UGizmoArrow(EAxis axis, AActor* Target): UGizmoBase(axis, Target) {}

void UGizmoArrow::Tick(float TickTime) {
	UGizmoBase::Tick(TickTime);
}

void UGizmoArrow::Destroy() {
	UGizmoBase::Destroy();
}

void UGizmoArrow::OnDragTick(int mx, int my) {}

void UGizmoArrow::OnRelease(int mx, int my) {}

void UGizmoArrow::OnClick(int mx, int my) {}