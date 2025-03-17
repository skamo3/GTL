#pragma once

#include "Resource/Types.h"

struct ObjData {
    TArray<FVertexSimple> vertices;
    TArray<uint32> indices;
};

class UResourceManager
{
public:
    UResourceManager();
    ~UResourceManager();

    void LoadPrimitives();
    
    ObjData LoadObj(FString filepath);

    void LoadTranslateGizmos();
    void LoadRotateGizmos();
    void LoadScaleGizmos();

    void Release();

    const TArray<FVertexSimple> GetPrimitiveVertexData(EPrimitiveType Type) const;
    const TArray<uint32> GetPrimitiveIndexData(EPrimitiveType Type) const;

    const TArray<FVertexUV> GetUVData() const { return UVQuadData; }

    const TArray<FVertexSimple> GetGizmoVertexData(EGizmoViewType Type) const;
    const TArray<uint32> GetGizmoIndexData(EGizmoViewType Type) const;

    void NewScene();
    void LoadScene(std::string SceneName);
    void SaveScene(std::string SceneName);

private:
    TArray<FVertexUV> UVQuadData;

    TMap<EPrimitiveType, TArray<FVertexSimple>> PrimitiveVertexDataMap;
    TMap<EGizmoViewType, TArray<FVertexSimple>> GizmoVertexDataMap;

    TMap<EPrimitiveType, TArray<uint32>> PrimitiveIndexDataMap;
    TMap<EGizmoViewType, TArray<uint32>> GizmoIndexDataMap;

private:
    UResourceManager(const UResourceManager& InResourceManager) = delete;  
    UResourceManager(UResourceManager&& InResourceManager) = delete;
    UResourceManager& operator=(const UResourceManager& InResourceManager) = delete;
    UResourceManager& operator=(UResourceManager&& InResourceManager) = delete;
};

