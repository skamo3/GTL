#include "pch.h"
#include "DXDRenderTarget.h"

UDXDRenderTarget::~UDXDRenderTarget()
{
    ReleaseRenderTarget();
}

HRESULT UDXDRenderTarget::CreateRenderTarget(ComPtr<ID3D11Device> DXDDevice, ComPtr<IDXGISwapChain> SwapChain, const D3D11_RENDER_TARGET_VIEW_DESC& RenderTargetViewDesc)
{
    HRESULT hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&FrameBuffer);
    if(FAILED(hr))
        return hr;

    hr = DXDDevice->CreateRenderTargetView(FrameBuffer.Get(), &RenderTargetViewDesc, &FrameBufferRTV);
    if (FAILED(hr))
        return hr;

    return S_OK;
}

void UDXDRenderTarget::ReleaseRenderTarget()
{
    if (FrameBuffer)
    {
        FrameBuffer.Reset();
    }

    if (FrameBufferRTV)
    {
        FrameBuffer.Reset();
    }
}
