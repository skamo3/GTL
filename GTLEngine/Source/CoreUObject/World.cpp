#include "pch.h"
#include "World.h"

#include "GameFrameWork/Actor.h"
#include "GameFrameWork/Camera.h"

#include "GameFrameWork/Shapes/Plane.h"
#include "GameFrameWork/Shapes/Sphere.h"
#include "GameFrameWork/Shapes/Cube.h"

#include "Engine.h"
#include "UI/UIManager.h"
#include "UI/ControlPanel.h"

UWorld* UWorld::CreateWorld()
{
	UWorld* NewWorld = new UWorld();
	NewWorld->MainCamera = new ACamera();

	NewWorld->SpawnActor<ACube>(TEXT("DefaultCude"), FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 90.f), FVector::OneVector, nullptr);
	NewWorld->SpawnActor<APlane>(TEXT("DefaultPlane"), FVector(0.f, 0.f, 2.f), FRotator(0.f, 0.f, 0.f), FVector::OneVector, nullptr);

	// TODO: 나중에 분리.
	NewWorld->CreateDefaultUI();

	NewWorld->MainCamera->SetActorLocation(FVector(-10.f, 0.f, 0.0f));

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
	for (AActor* Actor : ActiveActors)
	{
		if (Actor)
			Actor->Destroy();
	}
	ActiveActors.clear();
}

void UWorld::InitViewInfo()
{
	CachedViewInfo.ViewMatrix = FMatrix();
	CachedViewInfo.ProjectionMatrix = FMatrix();
	CachedViewInfo.ViewProjectionMatrix = FMatrix();
}

void UWorld::CreateDefaultUI()
{
	UUIManager* UIManager = UEngine::GetEngine().GetUIManager();
	if (UIManager)
	{
		UIManager->RegistUI(new UControlPanel());

	}
}
