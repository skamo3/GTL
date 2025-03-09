#include "pch.h"
#include "World.h"

#include "GameFrameWork/Actor.h"

UWorld* UWorld::CreateWorld(std::wstring WorldName)
{
	UWorld* NewWorld = new UWorld();
	NewWorld->SetName(WorldName);

    return NewWorld;
}

void UWorld::CameraTick(float TickTime)
{
	// 카메라 정보 업데이트.
	// 위치, 뭐 등등..
}

void UWorld::Tick(float TickTime)
{
	for (AActor* Actor : ActiveActors)
	{
		Actor->Tick(TickTime);
	}
}

void UWorld::Destroy()
{
}
