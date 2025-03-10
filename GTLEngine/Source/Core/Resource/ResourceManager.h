#pragma once

#include "Resource/Types.h"

class UResourceManager
{
public:
    UResourceManager();
    ~UResourceManager();

    void LoadPrimitives();

    void Release();

    const FVertexSimple* GetVertexInfo(EPrimitiveType Type) const;

private:
    TMap<EPrimitiveType, FVertexSimple*> VertexInfos;

private:
    UResourceManager(const UResourceManager& InResourceManager) = delete;  
    UResourceManager(UResourceManager&& InResourceManager) = delete;
    UResourceManager& operator=(const UResourceManager& InResourceManager) = delete;
    UResourceManager& operator=(UResourceManager&& InResourceManager) = delete;
};

