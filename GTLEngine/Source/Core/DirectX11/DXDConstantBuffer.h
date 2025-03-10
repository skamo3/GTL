#pragma once

#include "Resource/Types.h"

class UDXDConstantBuffer
{
public:
    UDXDConstantBuffer() = default;
    UDXDConstantBuffer(ComPtr<ID3D11Device> Device);

    void Release();

    HRESULT CreateBuffer(EConstantBufferType Type);

    ID3D11Buffer* GetConstantBuffer() const { return ConstantBuffer; }

private:
    ComPtr<ID3D11Device> DXDDevice;

    ID3D11Buffer* ConstantBuffer;
};

