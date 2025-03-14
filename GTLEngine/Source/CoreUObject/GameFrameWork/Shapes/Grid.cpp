#include "pch.h"
#include "CoreUObject/Components/GridComponent.h"
#include "Grid.h"

AGrid::AGrid(): AActor() {
	GridComponent = AddComponent<UGridComponent>(this);
	GridComponent->SetupAttachment(RootComponent);
}

void AGrid::Tick(float TickTime) {
	AActor::Tick(TickTime);
}

void AGrid::Destroy() {
	AActor::Destroy();
}
