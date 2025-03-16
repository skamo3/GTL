#include "pch.h"
#include "ResourceManager.h"

#include "Resource/Shape/PrimitiveShape.h"

#include "SimpleJSON/json.hpp"
#include <fstream>
#include <sstream>

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
    LoadArrowGizmos();
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

    uint64 LineVertexNum = sizeof(LineVertices) / sizeof(FVertexSimple);
    VertexDataMap[EPrimitiveType::Line] = TArray<FVertexSimple>(LineVertices, LineVertices + LineVertexNum);

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

    uint64 GridVertexNum = 1000;
    float offset = static_cast<float>(GridVertexNum / 2) / 4;
    TArray<FVertexSimple>& grid = VertexDataMap[EPrimitiveType::Grid] = TArray<FVertexSimple>();
    grid.reserve(GridVertexNum);
    for ( int i = 0; i < GridVertexNum / 4; ++i ) {
        float f = static_cast<float>(i);
        grid.push_back({ f - offset, offset,  0.f,    1.0f, 1.0f, 1.0f, 1.0f });
        grid.push_back({ f - offset, -offset, 0.f,    1.0f, 1.0f, 1.0f, 1.0f });
        grid.push_back({ offset, f - offset,  0.f,    1.0f, 1.0f, 1.0f, 1.0f });
        grid.push_back({ -offset, f - offset, 0.f,    1.0f, 1.0f, 1.0f, 1.0f });
    }

    uint64 BoundingBoxVertexNum = sizeof(BoundingBoxVertices) / sizeof(FVertexSimple);
    VertexDataMap[EPrimitiveType::BoundingBox] = TArray<FVertexSimple>(BoundingBoxVertices, BoundingBoxVertices + BoundingBoxVertexNum);
}

void UResourceManager::LoadArrowGizmos()
{
    // OBJ 파일 경로 (예: AxisArrow.obj)
    FString filepath = L"Source/Core/Resource/Shape/AxisArrow.obj";
    std::ifstream objFile(filepath.c_str());
    if (!objFile)
    {
        // 파일 열기 실패 시 처리
        return;
    }

    std::string line;
    std::vector<FVector> positions;
    TArray<FVertexSimple> vertices;
    TArray<uint32> indices;

    while (std::getline(objFile, line)) {
        std::istringstream lineStream(line);
        std::string type;
        lineStream >> type;

        if (type == "v") // Vertex position
        {
            FVector vertex;
            lineStream >> vertex.X >> vertex.Y >> vertex.Z;
            FVertexSimple vertexSimple{ vertex.X, vertex.Y, vertex.Z, 0.f,0.f, 0.f, 1.f };
            vertices.push_back(vertexSimple);
            positions.push_back(vertex);
        }
        else if (type == "f") // Face
        {
            std::vector<uint32_t> faceIndices;
            uint32_t index;

            while (lineStream >> index) {
                faceIndices.push_back(index - 1);
            }

            for (size_t i = 1; i + 1 < faceIndices.size(); ++i) {
                indices.push_back(faceIndices[0]);
                indices.push_back(faceIndices[i]);
                indices.push_back(faceIndices[i + 1]);
            }
        }

    }
    objFile.close();

    // 이제 tmpVertices에 읽어들인 정점을 3개의 배열로 복사하면서 색상을 지정합니다.
    TArray<FVertexSimple> XVertices;
    TArray<FVertexSimple> YVertices;
    TArray<FVertexSimple> ZVertices;

    // tmpVertices의 각 정점을 복사하여 각 배열에 넣음
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        FVertexSimple xVert = vertices[i];
        FVertexSimple yVert = vertices[i];
        FVertexSimple zVert = vertices[i];

        // X축은 빨간색 (1,0,0)
        xVert.R = 1.f; xVert.G = 0.f; xVert.B = 0.f;
        // Y축은 녹색 (0,1,0)
        yVert.R = 0.f; yVert.G = 1.f; yVert.B = 0.f;
        // Z축은 파란색 (0,0,1)
        zVert.R = 0.f; zVert.G = 0.f; zVert.B = 1.f;

        XVertices.push_back(xVert);
        YVertices.push_back(yVert);
        ZVertices.push_back(zVert);
    }

    // 이제 각 축에 해당하는 정점 배열을 VertexDataMap에 저장합니다.
    // EGizmoType 또는 EPrimitiveType에 맞게 열거형 값을 사용하세요.
    VertexDataMap[EPrimitiveType::XArrow] = XVertices;
    VertexDataMap[EPrimitiveType::YArrow] = YVertices;
    VertexDataMap[EPrimitiveType::ZArrow] = ZVertices;
    IndexDataMap[EPrimitiveType::XArrow] = indices;
    IndexDataMap[EPrimitiveType::YArrow] = indices;
    IndexDataMap[EPrimitiveType::ZArrow] = indices;
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

const TArray<uint32> UResourceManager::GetIndexData(EPrimitiveType Type) const
{
    if (IndexDataMap.contains(Type))
    {
        return IndexDataMap.find(Type)->second;
    }
    return TArray<uint32>();
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
