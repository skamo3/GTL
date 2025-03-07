#include "pch.h"
#include "DXDRenderTarget.h"

#include "DXDDevice.h"
#include "DXDSwapChain.h"

UDXDRenderTarget::~UDXDRenderTarget()
{
	ReleaseRenderTarget();
}

HRESULT UDXDRenderTarget::CreateRenderTarget(shared_ptr<UDXDDevice> DXDDevice, shared_ptr<UDXDSwapChain> SwapChain)
{

	HRESULT hr = SwapChain->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&FrameBuffer);
	if(FAILED(hr))
		return hr;
	
	// 렌더 타겟 뷰 생성
	D3D11_RENDER_TARGET_VIEW_DESC framebufferRTVdesc = {};
	framebufferRTVdesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB; // 색상 포맷
	framebufferRTVdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D; // 2D 텍스처

	hr = DXDDevice->GetDevice()->CreateRenderTargetView(FrameBuffer.Get(), &framebufferRTVdesc, &FrameBufferRTV);
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
