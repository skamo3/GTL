#include "pch.h"
#include "ResourceManager.h"

#include "Resource/Shape/PrimitiveShape.h"

#include "SimpleJSON/json.hpp"
#include <fstream>

#include "Engine.h"
#include "World.h"
#include "GameFrameWork/Actor.h"

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
    VertexDataMap[EPrimitiveType::Plane] = TArray<FVertexSimple>(TriangleVertices, TriangleVertices + TriangleVertexNum);

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

}

void UResourceManager::LoadScene(std::string SceneName)
{

}

void UResourceManager::SaveScene(std::string SceneName)
{
    UWorld* World = UEngine::GetEngine().GetWorld();
    if (!World)
        return;

    json::JSON Scene;

    TArray<AActor*> Actors = World->GetActors();
    TArray<USceneComponent*> RootComponents;
    for (AActor* Element : Actors)
        RootComponents.push_back(Element->GetRootComponent());

    uint32 key = 0;
    for (USceneComponent* Element : RootComponents)
    {
        Scene["Components"][key]["Location"] = json::FVectorToJSON(Element->GetComponentLocation());
        Scene["Components"][key]["Rotation"] = json::FRotatorToJSON(Element->GetComponentRotation());
        Scene["Components"][key]["Scale"] = json::FVectorToJSON(Element->GetComponentScale());

        TArray<USceneComponent*> stack;


        while (!Element->GetAllChildren().empty())
        {
            
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
    else {
    }
    
}
