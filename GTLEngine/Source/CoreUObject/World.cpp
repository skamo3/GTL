#include "pch.h"
#include "World.h"

#include "GameFrameWork/Actor.h"

UWorld* UWorld::CreateWorld(string WorldName)
{
	UWorld* NewWorld = new UWorld();
	NewWorld->SetName(WorldName);

    return NewWorld;
}

void UWorld::Init()
{
}

void UWorld::Update(float TickTime)
{
	for (AActor* Actor : ActiveActors)
	{
		Actor->Update(TickTime);
	}
}

void UWorld::Destroy()
{
}
