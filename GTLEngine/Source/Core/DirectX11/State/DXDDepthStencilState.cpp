#include "pch.h"
#include "DXDDepthStencilState.h"

UDXDDepthStencilState::~UDXDDepthStencilState()
{
    ReleaseDepthStencilState();
}

HRESULT UDXDDepthStencilState::CreateDepthStencilState(ComPtr<ID3D11Device> Device)
{
    // 기본 DepthStencilState
    HRESULT hr = S_OK;
    DepthStencilStates.resize(2);
    D3D11_DEPTH_STENCIL_DESC DepthStencilDesc = {};
    memset(&DepthStencilDesc, 0, sizeof(DepthStencilDesc));
    DepthStencilDesc.DepthEnable = TRUE;
    DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
    hr = Device->CreateDepthStencilState(&DepthStencilDesc, &DepthStencilStates[0]);
    if (FAILED(hr))
    {
        return hr;
    }

    // 깊이 무시하는 기즈모용 DepthStencilState
    DepthStencilDesc.DepthEnable = FALSE;
    DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
    DepthStencilDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
    hr = Device->CreateDepthStencilState(&DepthStencilDesc, &DepthStencilStates[1]);
    if (FAILED(hr))
    {
        return hr;
    }
    return S_OK;
}

void UDXDDepthStencilState::ReleaseDepthStencilState()
{
    if (DepthStencilStates[0])
    {
        DepthStencilStates[0]->Release();
    }
    if (DepthStencilStates[1])
    {
        DepthStencilStates[1]->Release();
    }
}