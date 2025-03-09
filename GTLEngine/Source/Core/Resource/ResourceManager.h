#pragma once

#include "Resource/VertexTypes.h"

class UResourceManager
{
public:
    UResourceManager();
    ~UResourceManager();

    void LoadPrimitives();

    const FVertexSimple* GetVertexInfo(const std::wstring& PrimitiveName) const;

private:
    TMap<std::wstring, FVertexSimple*> VertexInfos;

private:
    UResourceManager(const UResourceManager& InResourceManager) = delete;
    UResourceManager(UResourceManager&& InResourceManager) = delete;
    UResourceManager& operator=(const UResourceManager& InResourceManager) = delete;
    UResourceManager& operator=(UResourceManager&& InResourceManager) = delete;
};

