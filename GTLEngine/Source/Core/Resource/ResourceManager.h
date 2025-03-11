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

private:
    TMap<EPrimitiveType, TArray<FVertexSimple>> VertexDataMap;

private:
    UResourceManager(const UResourceManager& InResourceManager) = delete;  
    UResourceManager(UResourceManager&& InResourceManager) = delete;
    UResourceManager& operator=(const UResourceManager& InResourceManager) = delete;
    UResourceManager& operator=(UResourceManager&& InResourceManager) = delete;
};

