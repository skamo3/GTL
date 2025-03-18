#include "pch.h"
#include "Line.h"
#include "CoreUObject/Components/LineComponent.h"

ALine::ALine() {
	LineComponent = AddComponent<ULineComponent>(this);
}

void ALine::SetRay(FRay ray) {
	LineComponent = AddComponent<ULineComponent>(
		this,
		ray.Origin,
		FRotator::ZeroRotator,
		FVector(100.f, 0.f, 0.f)
	);
	LineComponent->SetDirection(FMatrix::MakeFromDirection(ray.Direction, FVector::UpVector));
}

void ALine::Tick(float TickTime) {
	AActor::Tick(TickTime);
}

void ALine::Destroy() {
	AActor::Destroy();
}
