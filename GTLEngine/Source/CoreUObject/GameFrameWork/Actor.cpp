#include "pch.h"
#include "Actor.h"

#include "Components/SceneComponent.h"

AActor::AActor()
	: Owner(nullptr)
{
	RootComponent = new USceneComponent();
}

void AActor::Tick(float TickTime)
{
	// RootComponent 기준으로 Child 불러서 업데이트.
	RootComponent->Tick(TickTime);
}

void AActor::Destroy()
{
	if (RootComponent)
	{
		RootComponent->Destroy();
		delete RootComponent;
		RootComponent = nullptr;
	}
}

void AActor::SetOwner(AActor* InOwner)
{
	Owner = InOwner;
}
