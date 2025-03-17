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
    // 평면형 UV 데이터 생성.
    UVQuadData = TArray<FVertexUV>(QuadVertices, QuadVertices + sizeof(QuadVertices) / sizeof(FVertexUV));
    LoadPrimitives();
    LoadTranslateGizmos();
}

UResourceManager::~UResourceManager()
{
    Release();
}

ObjData UResourceManager::LoadObj(FString filepath)
{
    std::ifstream objFile(filepath.c_str());
    ObjData data;
    if (!objFile)
        return data; // 실패 시 빈 구조체 반환

    std::string line;
    while (std::getline(objFile, line)) {
        std::istringstream lineStream(line);
        std::string type;
        lineStream >> type;

        if (type == "v") { // Vertex position
            FVertexSimple vertex;
            //lineStream >> vertex.X >> vertex.Y >> vertex.Z >> vertex.R >> vertex.G >> vertex.B; color 있을경우
            lineStream >> vertex.X >> vertex.Y >> vertex.Z;
            FVertexSimple vertexSimple{ vertex.X, vertex.Y, vertex.Z, 0.f, 0.f, 0.f, 1.f };
            data.vertices.push_back(vertexSimple);
        }
        else if (type == "f") { // Face
            std::vector<uint32> faceIndices;
            uint32 index;

            while (lineStream >> index) {
                faceIndices.push_back(index - 1);
            }
            for (size_t i = 1; i + 1 < faceIndices.size(); ++i) {
                data.indices.push_back(faceIndices[0]);
                data.indices.push_back(faceIndices[i]);
                data.indices.push_back(faceIndices[i + 1]);
            }
        }
    }
    objFile.close();
    return data;
}

void UResourceManager::LoadPrimitives()
{
    PrimitiveVertexDataMap[EPrimitiveType::Line] = {
        {0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f},
        {0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f},
    };

    uint64 LineVertexNum = sizeof(LineVertices) / sizeof(FVertexSimple);
    PrimitiveVertexDataMap[EPrimitiveType::Line] = TArray<FVertexSimple>(LineVertices, LineVertices + LineVertexNum);

    uint64 TriangleVertexNum = sizeof(TriangleVertices) / sizeof(FVertexSimple);
    PrimitiveVertexDataMap[EPrimitiveType::Triangle] = TArray<FVertexSimple>(TriangleVertices, TriangleVertices + TriangleVertexNum);

    uint64 SphereVertexNum = sizeof(SphereVertices) / sizeof(FVertexSimple);
    PrimitiveVertexDataMap[EPrimitiveType::Sphere] = TArray<FVertexSimple>(SphereVertices, SphereVertices + SphereVertexNum);

    uint64 CubeVertexNum = sizeof(CubeVertices) / sizeof(FVertexSimple);
    PrimitiveVertexDataMap[EPrimitiveType::Cube] = TArray<FVertexSimple>(CubeVertices, CubeVertices + CubeVertexNum);

    uint64 CylinderVertexNum = sizeof(CylinderVertices) / sizeof(FVertexSimple);
    PrimitiveVertexDataMap[EPrimitiveType::Cylinder] = TArray<FVertexSimple>(CylinderVertices, CylinderVertices + CylinderVertexNum);

    uint64 ConeVertexNum = sizeof(ConeVertices) / sizeof(FVertexSimple);
    PrimitiveVertexDataMap[EPrimitiveType::Cone] = TArray<FVertexSimple>(ConeVertices, ConeVertices + ConeVertexNum);

    uint64 GridVertexNum = 1000;
    float offset = static_cast<float>(GridVertexNum / 2) / 4;
    TArray<FVertexSimple>& grid = PrimitiveVertexDataMap[EPrimitiveType::Grid] = TArray<FVertexSimple>();
    grid.reserve(GridVertexNum);
    for ( int i = 0; i < GridVertexNum / 4; ++i ) {
        float f = static_cast<float>(i);
        grid.push_back({ f - offset, offset,  0.f,    1.0f, 1.0f, 1.0f, 1.0f });
        grid.push_back({ f - offset, -offset, 0.f,    1.0f, 1.0f, 1.0f, 1.0f });
        grid.push_back({ offset, f - offset,  0.f,    1.0f, 1.0f, 1.0f, 1.0f });
        grid.push_back({ -offset, f - offset, 0.f,    1.0f, 1.0f, 1.0f, 1.0f });
    }

    uint64 BoundingBoxVertexNum = sizeof(BoundingBoxVertices) / sizeof(FVertexSimple);
    PrimitiveVertexDataMap[EPrimitiveType::BoundingBox] = TArray<FVertexSimple>(BoundingBoxVertices, BoundingBoxVertices + BoundingBoxVertexNum);
}

void UResourceManager::LoadTranslateGizmos()
{
    ObjData Obj = LoadObj(L"Resource/Shape/GizmoTranslate.obj");

    // 이제 tmpVertices에 읽어들인 정점을 3개의 배열로 복사하면서 색상을 지정합니다.
    TArray<FVertexSimple> XVertices;
    TArray<FVertexSimple> YVertices;
    TArray<FVertexSimple> ZVertices;

    // tmpVertices의 각 정점을 복사하여 각 배열에 넣음
    for (size_t i = 0; i < Obj.vertices.size(); ++i)
    {
        FVertexSimple xVert = Obj.vertices[i];
        FVertexSimple yVert = Obj.vertices[i];
        FVertexSimple zVert = Obj.vertices[i];

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
    // EGizmoViewType 또는 EPrimitiveType에 맞게 열거형 값을 사용하세요.
    GizmoVertexDataMap[EGizmoViewType::XTranslate] = XVertices;
    GizmoVertexDataMap[EGizmoViewType::YTranslate] = YVertices;
    GizmoVertexDataMap[EGizmoViewType::ZTranslate] = ZVertices;
    GizmoIndexDataMap[EGizmoViewType::XTranslate] = Obj.indices;
    GizmoIndexDataMap[EGizmoViewType::YTranslate] = Obj.indices;
    GizmoIndexDataMap[EGizmoViewType::ZTranslate] = Obj.indices;
}

void UResourceManager::LoadRotateGizmos()
{
    ObjData Obj = LoadObj(L"Resource/Shape/GizmoRotate.obj");

    // 이제 tmpVertices에 읽어들인 정점을 3개의 배열로 복사하면서 색상을 지정합니다.
    TArray<FVertexSimple> XVertices;
    TArray<FVertexSimple> YVertices;
    TArray<FVertexSimple> ZVertices;

    // tmpVertices의 각 정점을 복사하여 각 배열에 넣음
    for (size_t i = 0; i < Obj.vertices.size(); ++i)
    {
        FVertexSimple xVert = Obj.vertices[i];
        FVertexSimple yVert = Obj.vertices[i];
        FVertexSimple zVert = Obj.vertices[i];

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
    // EGizmoViewType 또는 EGizmoViewType에 맞게 열거형 값을 사용하세요.
    GizmoVertexDataMap[EGizmoViewType::XRotate] = XVertices;
    GizmoVertexDataMap[EGizmoViewType::YRotate] = YVertices;
    GizmoVertexDataMap[EGizmoViewType::ZRotate] = ZVertices;
    GizmoIndexDataMap[EGizmoViewType::XRotate] = Obj.indices;
    GizmoIndexDataMap[EGizmoViewType::YRotate] = Obj.indices;
    GizmoIndexDataMap[EGizmoViewType::ZRotate] = Obj.indices;
}

void UResourceManager::LoadScaleGizmos()
{
    ObjData Obj = LoadObj(L"Resource/Shape/GizmoScale.obj");

    // 이제 tmpVertices에 읽어들인 정점을 3개의 배열로 복사하면서 색상을 지정합니다.
    TArray<FVertexSimple> XVertices;
    TArray<FVertexSimple> YVertices;
    TArray<FVertexSimple> ZVertices;

    // tmpVertices의 각 정점을 복사하여 각 배열에 넣음
    for (size_t i = 0; i < Obj.vertices.size(); ++i)
    {
        FVertexSimple xVert = Obj.vertices[i];
        FVertexSimple yVert = Obj.vertices[i];
        FVertexSimple zVert = Obj.vertices[i];

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
    // EGizmoViewType 또는 EGizmoViewType에 맞게 열거형 값을 사용하세요.
    GizmoVertexDataMap[EGizmoViewType::XScale] = XVertices;
    GizmoVertexDataMap[EGizmoViewType::YScale] = YVertices;
    GizmoVertexDataMap[EGizmoViewType::ZScale] = ZVertices;
    GizmoIndexDataMap[EGizmoViewType::XScale] = Obj.indices;
    GizmoIndexDataMap[EGizmoViewType::YScale] = Obj.indices;
    GizmoIndexDataMap[EGizmoViewType::ZScale] = Obj.indices;
}

void UResourceManager::Release()
{
    for (auto& [Type, Info] : PrimitiveVertexDataMap)
    {
        Info.clear();
    }
    PrimitiveVertexDataMap.clear();
}

const TArray<FVertexSimple> UResourceManager::GetPrimitiveVertexData(EPrimitiveType Type) const
{
    if (PrimitiveVertexDataMap.contains(Type))
    {
        return PrimitiveVertexDataMap.find(Type)->second;
    }
	return TArray<FVertexSimple>();
}

const TArray<uint32> UResourceManager::GetPrimitiveIndexData(EPrimitiveType Type) const
{
    if (PrimitiveIndexDataMap.contains(Type))
    {
        return PrimitiveIndexDataMap.find(Type)->second;
    }
    return TArray<uint32>();
}

const TArray<FVertexSimple> UResourceManager::GetGizmoVertexData(EGizmoViewType Type) const
{
    if (GizmoVertexDataMap.contains(Type))
    {
        return GizmoVertexDataMap.find(Type)->second;
    }
    return TArray<FVertexSimple>();
}

const TArray<uint32> UResourceManager::GetGizmoIndexData(EGizmoViewType Type) const
{
    if (GizmoIndexDataMap.contains(Type))
    {
        return GizmoIndexDataMap.find(Type)->second;
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
