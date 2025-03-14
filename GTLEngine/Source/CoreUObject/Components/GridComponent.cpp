#include "pch.h"
#include "GridComponent.h"

UGridComponent::UGridComponent() {
	PrimitiveType = EPrimitiveType::Grid;
	SetRelativeLocation(FVector(0, -10, 0));
}

void UGridComponent::Tick(float TickTime) {
}

void UGridComponent::Destroy() {}