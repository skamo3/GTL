#include "pch.h"
#include "Cone.h"
#include "Components/ConeComponent.h"

ACone::ACone()
	: AActor()
{
	ConeComponent = AddComponent<UConeComponent>(this);
	ConeComponent->SetupAttachment(RootComponent);
}

void ACone::Tick(float TickTime)
{
	AActor::Tick(TickTime);
}

void ACone::Destroy()
{
	AActor::Destroy();
}