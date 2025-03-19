#include "pch.h"
#include "World.h"

#include "GameFrameWork/Actor.h"
#include "GameFrameWork/Camera.h"

#include "GameFrameWork/Shapes/Triangle.h"
#include "GameFrameWork/Shapes/Sphere.h"
#include "GameFrameWork/Shapes/Cube.h"
#include "GameFrameWork/Shapes/Cylinder.h"
#include "GameFrameWork/Shapes/Cone.h"

#include "Engine.h"
#include "UI/UIManager.h"
#include "UI/ControlPanel.h"
#include "UI/ConsolePanel.h"
#include "UI/PropertyPanel.h"
#include "UI/SceneManager.h"

UWorld* UWorld::CreateWorld()
{
	UWorld* NewWorld = new UWorld();
	NewWorld->CreateDefaultUI();

	NewWorld->MainCamera = new ACamera();
	NewWorld->SpawnActor<ACube>(TEXT("DefaultCude"), FVector(0.f, 2.f, 0.f), FRotator(0.f, 0.f, 90.f), FVector::OneVector, nullptr);
	NewWorld->SpawnActor<ASphere>(TEXT("DefaultSphere"), FVector(0.f, 0.f, 2.f), FRotator(0.f, 0.f, 45.f), FVector(1.0f, 2.0f, 1.0f), nullptr);

	// TODO: 나중에 분리.
	

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
	IClickable::GetClickableList().clear();
	IDragable::GetClickableList().clear();
	UEngine::GetEngine().GetGizmoManager()->ClearSelected();
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
		UIManager->RegistUI(new UConsolePanel());
		UIManager->RegistUI(new UPropertyPanel());
		UIManager->RegistUI(new USceneManager());
	}
}
