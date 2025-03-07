#include "pch.h"
#include "DXDSwapChain.h"

#include "DXDDevice.h"

UDXDSwapChain::~UDXDSwapChain()
{
    ReleaseSwapChain();
}

HRESULT UDXDSwapChain::CreateSwapChain(HWND hWnd, shared_ptr<UDXDDevice> Device, D3D11_VIEWPORT& ViewportInfo)
{
	ComPtr<IDXGIDevice> dxgiDevice;

    DXGI_SWAP_CHAIN_DESC swapchaindesc = {};
    swapchaindesc.BufferDesc.Width = 0; // 창 크기에 맞게 자동으로 설정
    swapchaindesc.BufferDesc.Height = 0; // 창 크기에 맞게 자동으로 설정
    swapchaindesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // 색상 포맷
    swapchaindesc.SampleDesc.Count = 1; // 멀티 샘플링 비활성화
    swapchaindesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 렌더 타겟으로 사용
    swapchaindesc.BufferCount = 2; // 더블 버퍼링
    swapchaindesc.OutputWindow = hWnd; // 렌더링할 창 핸들
    swapchaindesc.Windowed = TRUE; // 창 모드
    swapchaindesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // 스왑 방식

    ComPtr<IDXGIDevice> DxgiDevice;
    HRESULT hr = Device->GetDevice()->QueryInterface(__uuidof(DxgiDevice), (void**)&DxgiDevice);
    if (FAILED(hr))
        return hr;

    ComPtr<IDXGIAdapter> Adapter;
    hr = DxgiDevice->GetAdapter(&Adapter);
    if (FAILED(hr))
        return hr;

    ComPtr<IDXGIFactory> Factory;
    hr = Adapter->GetParent(__uuidof(IDXGIFactory), (void**)&Factory);
    if (FAILED(hr))
        return hr;

    hr = Factory->CreateSwapChain(Device->GetDevice().Get(), &swapchaindesc, &SwapChain);
    if (FAILED(hr))
        return hr;
    
    hr = SwapChain->GetDesc(&swapchaindesc);
    if (FAILED(hr))
        return hr;
    ViewportInfo = { 0.0f, 0.0f, (float)swapchaindesc.BufferDesc.Width, (float)swapchaindesc.BufferDesc.Height, 0.0f, 1.0f };

    return S_OK;
}

void UDXDSwapChain::ReleaseSwapChain()
{
    if (SwapChain)
    {
        SwapChain->Release();
        SwapChain.Reset();
    }
}

void UDXDSwapChain::Present()
{
}

void UDXDSwapChain::Resize()
{
}
