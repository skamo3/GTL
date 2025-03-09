#include "pch.h"
#include "DXDRasterizerState.h"

UDXDRasterizerState::~UDXDRasterizerState()
{
    ReleaseRasterizerState();
}

HRESULT UDXDRasterizerState::CreateRasterizerState(ComPtr<ID3D11Device> Device)
{
    D3D11_RASTERIZER_DESC SolidRasterizerDesc = {};
    SolidRasterizerDesc.FillMode = D3D11_FILL_SOLID; // 채우기 모드
    SolidRasterizerDesc.CullMode = D3D11_CULL_BACK; // 백 페이스 컬링
    
    HRESULT hr = Device->CreateRasterizerState(&SolidRasterizerDesc, &RasterizerState);
    if (FAILED(hr))
        return hr;
    
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
