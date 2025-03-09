#include "pch.h"
#include "ResourceManager.h"

#include "Resource/Shape/PrimitiveShape.h"

UResourceManager::UResourceManager()
{
    LoadPrimitives();
}

UResourceManager::~UResourceManager()
{
    for (TPair<const std::wstring, FVertexSimple*>& Vertex : VertexInfos)
    {
        if (Vertex.second)
        {
            delete[] Vertex.second;
        }
    }
    VertexInfos.clear();
}

void UResourceManager::LoadPrimitives()
{
    VertexInfos[L"Triangle"] = TriangleVertices;
    VertexInfos[L"Cylinder"] = CylinderVertices;
    VertexInfos[L"Cube"] = CubeVertices;
    VertexInfos[L"Sphere"] = SphereVertices;
    VertexInfos[L"Cone"] = ConeVertices;
}

const FVertexSimple* UResourceManager::GetVertexInfo(const std::wstring& PrimitiveName) const
{
    if (VertexInfos.find(PrimitiveName) != VertexInfos.end())
    {
        return VertexInfos.at(PrimitiveName);
    }
    return nullptr;
}
