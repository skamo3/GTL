#include "pch.h"
#include "ResourceManager.h"

#include "Resource/Shape/PrimitiveShape.h"

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
    VertexInfos[EPrimitiveType::Triangle] = TriangleVertices;
    VertexInfos[EPrimitiveType::Sphere] = SphereVertices;
    VertexInfos[EPrimitiveType::Cube] = CubeVertices;
    VertexInfos[EPrimitiveType::Cylinder] = CylinderVertices;
    VertexInfos[EPrimitiveType::Cone] = ConeVertices;
}

void UResourceManager::Release()
{
    for (auto& [Type, Info] : VertexInfos)
    {
        if (Info)
        {
            delete[] Info;
        }
    }
    VertexInfos.clear();
}

const FVertexSimple* UResourceManager::GetVertexInfo(EPrimitiveType Type) const
{
    if (VertexInfos.contains(Type))
    {
        return VertexInfos.at(Type);
    }
    return nullptr;
}
