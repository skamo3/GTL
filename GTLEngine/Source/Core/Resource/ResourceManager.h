#pragma once

#include "Resource/Types.h"

class UResourceManager
{
public:
    UResourceManager();
    ~UResourceManager();

    void LoadPrimitives();

    void Release();

    const TArray<FVertexSimple> GetVertexData(EPrimitiveType Type) const;
    const TArray<FVertexUV> GetUVData() const { return UVQuadData; }

    void NewScene();
    void LoadScene(std::string SceneName);
    void SaveScene(std::string SceneName);

private:
    TMap<EPrimitiveType, TArray<FVertexSimple>> VertexDataMap;
    TArray<FVertexUV> UVQuadData;

private:
    UResourceManager(const UResourceManager& InResourceManager) = delete;  
    UResourceManager(UResourceManager&& InResourceManager) = delete;
    UResourceManager& operator=(const UResourceManager& InResourceManager) = delete;
    UResourceManager& operator=(UResourceManager&& InResourceManager) = delete;
};

