#pragma once

#include "Resource/Types.h"

class UResourceManager
{
public:
    UResourceManager();
    ~UResourceManager();

    void LoadPrimitives();

    void LoadArrowGizmos();

    void Release();

    const TArray<FVertexSimple> GetVertexData(EPrimitiveType Type) const;
    const TArray<uint32> GetIndexData(EPrimitiveType Type) const;

    void NewScene();
    void LoadScene(std::string SceneName);
    void SaveScene(std::string SceneName);

private:
    TMap<EPrimitiveType, TArray<FVertexSimple>> VertexDataMap;
    TMap<EPrimitiveType, TArray<uint32>> IndexDataMap;

private:
    UResourceManager(const UResourceManager& InResourceManager) = delete;  
    UResourceManager(UResourceManager&& InResourceManager) = delete;
    UResourceManager& operator=(const UResourceManager& InResourceManager) = delete;
    UResourceManager& operator=(UResourceManager&& InResourceManager) = delete;
};

