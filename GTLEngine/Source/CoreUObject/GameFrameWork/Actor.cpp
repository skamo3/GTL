#include "pch.h"
#include "Actor.h"

#include "Components/SceneComponent.h"

AActor::AActor()
	: Owner(nullptr)
{
	RootComponent = AddComponent<USceneComponent>(this);
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

FVector AActor::GetActorLocation() const
{
	return RootComponent->GetComponentLocation();
}

FVector AActor::GetActorRotation() const
{
	return RootComponent->GetComponentRotation();
}

FVector AActor::GetActorScale() const
{
	return RootComponent->GetComponentScale();
}