#include "pch.h"
#include "World.h"

#include "GameFrameWork/Actor.h"
#include "GameFrameWork/Camera.h"

UWorld* UWorld::CreateWorld()
{
	UWorld* NewWorld = new UWorld();

    return NewWorld;
}

void UWorld::CameraTick(float TickTime)
{
	// 카메라 정보 업데이트.
	// 위치, 뭐 등등..
	MainCamera->Tick(TickTime);
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
