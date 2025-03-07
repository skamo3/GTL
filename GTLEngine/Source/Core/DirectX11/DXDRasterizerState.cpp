#include "pch.h"
#include "DXDRasterizerState.h"

#include "DXDDevice.h"

UDXDRasterizerState::~UDXDRasterizerState()
{
    ReleaseRasterizerState();
}

HRESULT UDXDRasterizerState::CreateRasterizerState(shared_ptr<UDXDDevice> Device)
{
    D3D11_RASTERIZER_DESC SolidRasterizerDesc = {};
    SolidRasterizerDesc.FillMode = D3D11_FILL_SOLID; // 채우기 모드
    SolidRasterizerDesc.CullMode = D3D11_CULL_BACK; // 백 페이스 컬링

    HRESULT hr = Device->GetDevice()->CreateRasterizerState(&SolidRasterizerDesc, &RasterizerState);
    if (FAILED(hr))
        return hr;
    
    D3D11_RASTERIZER_DESC WireRasterizerDesc = {};
    WireRasterizerDesc.FillMode = D3D11_FILL_WIREFRAME; // 와이어 모드
    WireRasterizerDesc.CullMode = D3D11_CULL_BACK; // 백 페이스 컬링

    return S_OK;
}

void UDXDRasterizerState::ReleaseRasterizerState()
{
    if (RasterizerState)
    {
        RasterizerState->Release();
        RasterizerState.Reset();
    }
}
