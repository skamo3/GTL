#pragma once

class UDXDDevice;
class UDXDSwapChain;

class UDXDRenderTarget
{

public:
    UDXDRenderTarget() = default;
    ~UDXDRenderTarget();

public:
    HRESULT CreateRenderTarget(shared_ptr<UDXDDevice> DXDDevice, shared_ptr<UDXDSwapChain> SwapChain, const D3D11_RENDER_TARGET_VIEW_DESC& RenderTargetViewDesc);
    void ReleaseRenderTarget();


    ComPtr<ID3D11Texture2D>         GetFrameBuffer() const { return FrameBuffer; }
    ComPtr<ID3D11RenderTargetView>  GetFrameBufferRTV() const { return FrameBufferRTV; }
private:
    ComPtr<ID3D11Texture2D>         FrameBuffer = nullptr;
    ComPtr<ID3D11RenderTargetView>  FrameBufferRTV = nullptr;
};

