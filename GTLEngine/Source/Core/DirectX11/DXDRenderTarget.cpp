#include "pch.h"
#include "DXDRenderTarget.h"

#include "DXDDevice.h"
#include "DXDSwapChain.h"

UDXDRenderTarget::~UDXDRenderTarget()
{
	ReleaseRenderTarget();
}

HRESULT UDXDRenderTarget::CreateRenderTarget(shared_ptr<UDXDDevice> DXDDevice, shared_ptr<UDXDSwapChain> SwapChain, const D3D11_RENDER_TARGET_VIEW_DESC& RenderTargetViewDesc)
{
	HRESULT hr = SwapChain->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&FrameBuffer);
	if(FAILED(hr))
		return hr;

	hr = DXDDevice->GetDevice()->CreateRenderTargetView(FrameBuffer.Get(), &RenderTargetViewDesc, &FrameBufferRTV);
	if (FAILED(hr))
		return hr;

	return S_OK;
}

void UDXDRenderTarget::ReleaseRenderTarget()
{
	if (FrameBuffer)
	{
		FrameBuffer->Release();
		FrameBuffer.Reset();
	}

	if (FrameBufferRTV)
	{
		FrameBuffer->Release();
		FrameBuffer.Reset();
	}
}
