#include "pch.h"
#include "Triangle.h"
#include "Components/TriangleComponent.h"

ATriangle::ATriangle()
	: AActor()
{
	TriangleComponent = AddComponent<UTriangleComponent>(this);
	TriangleComponent->SetupAttachment(RootComponent);
}

void ATriangle::Tick(float TickTime)
{
	AActor::Tick(TickTime);
}

void ATriangle::Destroy()
{
	AActor::Destroy();
}
