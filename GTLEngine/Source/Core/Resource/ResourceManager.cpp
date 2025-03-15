#include "pch.h"
#include "ResourceManager.h"

#include "Resource/Shape/PrimitiveShape.h"

#include "SimpleJSON/json.hpp"
#include <fstream>

#include "Engine.h"
#include "World.h"
#include "GameFrameWork/Actor.h"

#include "GameFrameWork/Shapes/Triangle.h"
#include "GameFrameWork/Shapes/Sphere.h"
#include "GameFrameWork/Shapes/Cube.h"
#include "GameFrameWork/Shapes/Cylinder.h"
#include "GameFrameWork/Shapes/Cone.h"

UResourceManager::UResourceManager()
{
    LoadPrimitives();
}

UResourceManager::~UResourceManager()
{
    Release();
}

void UResourceManager::LoadPrimitives()
{
    VertexDataMap[EPrimitiveType::Line] = {
        {0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f},
        {0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f},
    };

    uint64 TriangleVertexNum = sizeof(TriangleVertices) / sizeof(FVertexSimple);
    VertexDataMap[EPrimitiveType::Triangle] = TArray<FVertexSimple>(TriangleVertices, TriangleVertices + TriangleVertexNum);

    uint64 SphereVertexNum = sizeof(SphereVertices) / sizeof(FVertexSimple);
    VertexDataMap[EPrimitiveType::Sphere] = TArray<FVertexSimple>(SphereVertices, SphereVertices + SphereVertexNum);

    uint64 CubeVertexNum = sizeof(CubeVertices) / sizeof(FVertexSimple);
    VertexDataMap[EPrimitiveType::Cube] = TArray<FVertexSimple>(CubeVertices, CubeVertices + CubeVertexNum);

    uint64 CylinderVertexNum = sizeof(CylinderVertices) / sizeof(FVertexSimple);
    VertexDataMap[EPrimitiveType::Cylinder] = TArray<FVertexSimple>(CylinderVertices, CylinderVertices + CylinderVertexNum);

    uint64 ConeVertexNum = sizeof(ConeVertices) / sizeof(FVertexSimple);
    VertexDataMap[EPrimitiveType::Cone] = TArray<FVertexSimple>(ConeVertices, ConeVertices + ConeVertexNum);
}

void UResourceManager::Release()
{
    for (auto& [Type, Info] : VertexDataMap)
    {
        Info.clear();
    }
    VertexDataMap.clear();
}

const TArray<FVertexSimple> UResourceManager::GetVertexData(EPrimitiveType Type) const
{
    if (VertexDataMap.contains(Type))
    {
        return VertexDataMap.find(Type)->second;
    }
	return TArray<FVertexSimple>();
}

void UResourceManager::NewScene()
{
    UWorld* World = UEngine::GetEngine().GetWorld();
    if (!World)
        return;
    World->Destroy();
}

void UResourceManager::LoadScene(std::string SceneName)
{
    std::ifstream inFile(SceneName + ".Scene");
    if (!inFile.is_open())
    {
        // 파일 열기 실패 처리
        return;
    }

    UWorld* World = UEngine::GetEngine().GetWorld();
    if (!World)
        return;
    World->Destroy();

    std::string jsonData((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    // JSON 파싱 (json::JSON::Load()는 JSON 문자열을 파싱하는 함수)
    json::JSON Scene = json::JSON::Load(jsonData);

    // "Actors" 객체를 순회합니다.
    for (const auto& actorPair : Scene["Actors"].ObjectRange())
    {
        // actorPair.first: 액터의 key, actorPair.second: 액터의 JSON 데이터
        const std::string& actorKey = actorPair.first;
        json::JSON actorJson = actorPair.second;

        FVector ActorLocation = JSONToFVector(actorJson["Location"]);
        FRotator ActorRotation = JSONToFRotator(actorJson["Rotation"]);
        FVector ActorScale = JSONToFVector(actorJson["Scale"]);
        std::string ActorType = actorJson["Type"].ToString();

        // 첫번째 자식 로드
        json::JSON childrenArray = actorJson["Children"];
        if (childrenArray.length() > 0)
        {
            json::JSON firstChildJson = childrenArray[0];
            FVector ChildLocation = JSONToFVector(firstChildJson["Location"]);
            FRotator ChildRotation = JSONToFRotator(firstChildJson["Rotation"]);
            FVector ChildScale = JSONToFVector(firstChildJson["Scale"]);
            std::string ChildType = firstChildJson["Type"].ToString();

            if (ChildType.find("Cube") != std::string::npos)
            {
                World->SpawnActor<ACube>(TEXT("DefaultCude"), ActorLocation, ActorRotation, ActorScale, nullptr);
            }
            if (ChildType.find("Sphere") != std::string::npos)
            {
                World->SpawnActor<ASphere>(TEXT("DefaultSphere"), ActorLocation, ActorRotation, ActorScale, nullptr);
            }
            if (ChildType.find("Triangle") != std::string::npos)
            {
                World->SpawnActor<ATriangle>(TEXT("DefaultTriangle"), ActorLocation, ActorRotation, ActorScale, nullptr);
            }
            if (ChildType.find("Cylinder") != std::string::npos)
            {
                World->SpawnActor<ACylinder>(TEXT("DefaultCylinder"), ActorLocation, ActorRotation, ActorScale, nullptr);
            }
            if (ChildType.find("Cone") != std::string::npos)
            {
                World->SpawnActor<ACone>(TEXT("DefaultCone"), ActorLocation, ActorRotation, ActorScale, nullptr);
            }
        }
    }
}

struct DFSItem {
    USceneComponent* Component;
    json::JSON* ParentChildrenArray;
};

void UResourceManager::SaveScene(std::string SceneName)
{
    UWorld* World = UEngine::GetEngine().GetWorld();
    if (!World)
        return;

    json::JSON Scene;

    TArray<AActor*> Actors = World->GetActors();
    TArray<USceneComponent*> RealRootComponents;

    for (AActor* Element : Actors)
        RealRootComponents.push_back(Element->GetRootComponent());

    uint32 key = 0;
    std::string ID;

    for (USceneComponent* RootComponent : RealRootComponents)
    {
        ID = std::to_string(key);

        json::JSON rootJson = json::Object();
        rootJson["Location"] = json::FVectorToJSON(RootComponent->GetComponentLocation());
        rootJson["Rotation"] = json::FRotatorToJSON(RootComponent->GetComponentRotation());
        rootJson["Scale"] = json::FVectorToJSON(RootComponent->GetComponentScale());
        rootJson["Type"] = typeid(*RootComponent).name();
        rootJson["Children"] = json::Array();

        Scene["Actors"][ID] = rootJson;

        TArray<DFSItem> stack;
        for (USceneComponent* Child : RootComponent->GetAllChildren())
        {
            DFSItem item;
            item.Component = Child;
            item.ParentChildrenArray = &Scene["Actors"][ID]["Children"];
            stack.push_back(item);
        }

        while (!stack.empty())
        {
            DFSItem currentItem = stack.back();
            stack.pop_back();
            USceneComponent* ChildComponent = currentItem.Component;

            json::JSON childJson = json::Object();
            childJson["Location"] = json::FVectorToJSON(ChildComponent->GetComponentLocation());
            childJson["Rotation"] = json::FRotatorToJSON(ChildComponent->GetComponentRotation());
            childJson["Scale"] = json::FVectorToJSON(ChildComponent->GetComponentScale());
            childJson["Type"] = typeid(*ChildComponent).name();
            childJson["Children"] = json::Array();

            currentItem.ParentChildrenArray->append(childJson);
            int lastIndex = currentItem.ParentChildrenArray->length() - 1;
            json::JSON& newChildJSON = (*currentItem.ParentChildrenArray)[lastIndex];
            for (USceneComponent* GrandChild : ChildComponent->GetAllChildren())
            {
                if (GrandChild != nullptr)
                {
                    DFSItem newItem;
                    newItem.Component = GrandChild;
                    newItem.ParentChildrenArray = &newChildJSON["Children"];
                    stack.push_back(newItem);
                }
            }
        }
        key++;
    }
    std::string jsonData = Scene.dump();
    std::ofstream outFile(SceneName + ".Scene");
    if (outFile.is_open())
    {
        outFile << jsonData;
        outFile.close();
    }
}
