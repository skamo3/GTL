#include "pch.h"
#include "World.h"
#include "Engine.h"

#include "GameFrameWork/Actor.h"
#include "GameFrameWork/Camera.h"
#include "Asset/AssetManager.h"
#include "Asset/SceneAsset.h"
#include <Components/CubeComponent.h>
#include <Components/SphereComponent.h>


UWorld* UWorld::CreateWorld()
{
	UWorld* NewWorld = new UWorld();
	NewWorld->MainCamera = new ACamera();

	USceneAsset* defaultScene = UEngine::GetEngine().GetAssetManager()->LoadAsset<USceneAsset>(FAssetMetaData(L"DefaultScene", L"Resource/Scene/DefaultScene.Scene"));

	FSceneData sceneData = defaultScene->GetSceneData();

	NewWorld->ApplySceneData(sceneData);

    return NewWorld;
}

void UWorld::CameraTick(float TickTime)
{
	// 카메라 정보 업데이트.
	// 위치, 뭐 등등..
	//MainCamera->Tick(TickTime);
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

void UWorld::ApplySceneData(const FSceneData& sceneData)
{
	for (auto& primitive : sceneData.Primitives)
	{
		Primitive loadedPrimitive = primitive.second;
		FVector location = FVector(loadedPrimitive.Location[0], loadedPrimitive.Location[1], loadedPrimitive.Location[2]);
		FVector rotation = FVector(loadedPrimitive.Rotation[0], loadedPrimitive.Rotation[1], loadedPrimitive.Rotation[2]);
		FVector scale = FVector(loadedPrimitive.Scale[0], loadedPrimitive.Scale[1], loadedPrimitive.Scale[2]);
		if (loadedPrimitive.Type == L"Cube")
		{
			AActor* spawnedActor = SpawnActor<AActor>(L"Cube", location, rotation, scale, this);
			spawnedActor->GetRootComponent()->SetRelativeLocation(location);
			spawnedActor->GetRootComponent()->SetRelativeRotation(rotation);
			spawnedActor->GetRootComponent()->SetRelativeScale3D(scale);
			spawnedActor->AddComponent<UCubeComponent>(spawnedActor, location, rotation, scale);
		}
		else if (loadedPrimitive.Type == L"Sphere")
		{
			AActor* spawnedActor = SpawnActor<AActor>(L"Sphere", location, rotation, scale, this);
			spawnedActor->GetRootComponent()->SetRelativeLocation(location);
			spawnedActor->GetRootComponent()->SetRelativeRotation(rotation);
			spawnedActor->GetRootComponent()->SetRelativeScale3D(scale);
			spawnedActor->AddComponent<USphereComponent>(spawnedActor, location, rotation, scale);
		}
		else if (loadedPrimitive.Type == L"Triangle")
		{
			AActor* spawnedActor = SpawnActor<AActor>(L"Triangle", location, rotation, scale, this);
			spawnedActor->GetRootComponent()->SetRelativeLocation(location);
			spawnedActor->GetRootComponent()->SetRelativeRotation(rotation);
			spawnedActor->GetRootComponent()->SetRelativeScale3D(scale);
			spawnedActor->AddComponent<UCubeComponent>(spawnedActor, location, rotation, scale);
		}
		else if (loadedPrimitive.Type == L"Plane")
		{
			AActor* spawnedActor = SpawnActor<AActor>(L"Plane", location, rotation, scale, this);
			spawnedActor->GetRootComponent()->SetRelativeLocation(location);
			spawnedActor->GetRootComponent()->SetRelativeRotation(rotation);
			spawnedActor->GetRootComponent()->SetRelativeScale3D(scale);
			spawnedActor->AddComponent<UCubeComponent>(spawnedActor, location, rotation, scale);
		}
	}
}
