#include "pch.h"
#include "PlaneComponent.h"
#include "Utils/Math/Geometry.h"

UPlaneComponent::UPlaneComponent()
	: UPrimitiveComponent()
{
	PrimitiveType = EPrimitiveType::Plane;
	OriginalAABB[0] = FVector(-0.5f, -0.5f, 0.f);
	OriginalAABB[1] = FVector(0.5f, -0.5f, 0.f);
	OriginalAABB[2] = FVector(-0.5f, 0.5f, 0.f);
	OriginalAABB[3] = FVector(0.5f, 0.5f, 0.f);
	OriginalAABB[4] = FVector(-0.5f, -0.5f, 0.f);
	OriginalAABB[5] = FVector(0.5f, -0.5f, 0.f);
	OriginalAABB[6] = FVector(-0.5f, 0.5f, 0.f);
	OriginalAABB[7] = FVector(0.5f, 0.5f, 0.f);
}

void UPlaneComponent::Tick(float TickTime)
{
}

void UPlaneComponent::Destroy()
{
}
