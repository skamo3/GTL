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
	UWorld* NewWorld = FObjectFactory::ConstructObject<UWorld>();

	// TODO: 나중에 분리.

	NewWorld->MainCamera = NewWorld->SpawnActor<ACamera>(TEXT("MainCamera"), FVector(0.f, 2.f, 0.f), FRotator(0.f, 0.f, 0.f), FVector::OneVector, nullptr);
	NewWorld->MainCamera->SetActorLocation(FVector(-10.f, 0.f, 0.0f));

    return NewWorld;
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
		{
			Actor->Destroy();
			FObjectFactory::DestroyObject(Actor);
		}
	}
	MainCamera = nullptr;
	ActiveActors.clear();
	/*IClickable::GetClickableList().clear();
	IDragable::GetClickableList().clear();*/
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
		
		//UIManager->RegistUI(new UControlPanel());
		//UIManager->RegistUI(new UConsolePanel());
		//UIManager->RegistUI(new UPropertyPanel());
		//UIManager->RegistUI(new USceneManager());
		UIManager->RegistUI(FObjectFactory::ConstructObject<UControlPanel>());
		UIManager->RegistUI(FObjectFactory::ConstructObject<UConsolePanel>());
		UIManager->RegistUI(FObjectFactory::ConstructObject<UPropertyPanel>());
		UIManager->RegistUI(FObjectFactory::ConstructObject<USceneManager>());
	}
}
