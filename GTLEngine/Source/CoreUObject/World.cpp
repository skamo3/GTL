#include "pch.h"
#include "World.h"

#include "GameFrameWork/Actor.h"
#include "GameFrameWork/Camera.h"

#include "Components/CubeComponent.h"
#include <Components/SphereComponent.h>
#include "Components/PlaneComponent.h"

#include "Engine.h"
#include "UI/UIManager.h"
#include "UI/ControlPanel.h"

UWorld* UWorld::CreateWorld()
{
	UWorld* NewWorld = new UWorld();
	NewWorld->MainCamera = new ACamera();

	// TODO: PlayerState는 임시 액터로, 월드의 멤버 변수로 변경해야함.
	AActor* PlayerState = NewWorld->SpawnActor<AActor>(TEXT("PlayerState"), FVector(), FVector(), FVector(), nullptr);
	PlayerState->SetName(TEXT("PlayerState"));
	 
	AActor* CubePrimitive = NewWorld->SpawnActor<AActor>(TEXT(""), FVector(0.f, 0.f, 0.f), FVector(0.f, 0.f, 0.f), FVector::OneVector, nullptr);
	CubePrimitive->SetName(TEXT("CubePrimitive"));
	CubePrimitive->AddComponent<UPlaneComponent>(CubePrimitive);
	CubePrimitive->GetComponentByClass<UPlaneComponent>()->SetName(TEXT("UCubeComponent"));

	// TODO: 나중에 따로 추가.
	NewWorld->CreateDefaultUI();

	NewWorld->MainCamera->SetActorLocation(FVector(0.f, 0.f, -10.f));

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

void UWorld::CreateDefaultUI()
{
	UUIManager* UIManager = UEngine::GetEngine().GetUIManager();
	if (UIManager)
	{
		UIManager->RegistUI(new UControlPanel());

	}
}
