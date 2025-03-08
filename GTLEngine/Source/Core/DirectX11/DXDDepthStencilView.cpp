#include "pch.h"
#include "DXDRasterizerState.h"

#include "DXDDepthStencilView.h"

UDXDDepthStencilView::~UDXDDepthStencilView()
{
    ReleaseDepthStencilView();
}

HRESULT UDXDDepthStencilView::CreateDepthStencilView(ComPtr<ID3D11Device> Device)
{
    D3D11_TEXTURE2D_DESC DepthStencilBufferDesc;

	DepthStencilBufferDesc.Width = 0;
	DepthStencilBufferDesc.Height = 0;
	DepthStencilBufferDesc.MipLevels = 1;
	DepthStencilBufferDesc.ArraySize = 1;
	DepthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthStencilBufferDesc.SampleDesc.Count = 1;
	DepthStencilBufferDesc.SampleDesc.Quality = 0;
	DepthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	DepthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; //뎁스스텐실 버퍼로 사용하겟다는 의지!
	DepthStencilBufferDesc.CPUAccessFlags = 0;
	DepthStencilBufferDesc.MiscFlags = 0;

	Device->CreateTexture2D(&DepthStencilBufferDesc, nullptr, &DepthStencilBuffer);

	D3D11_DEPTH_STENCIL_VIEW_DESC DepthStencilViewDesc;
	ZeroMemory(&DepthStencilViewDesc, sizeof(DepthStencilViewDesc));
	DepthStencilViewDesc.Format = DepthStencilBufferDesc.Format;
	DepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	DepthStencilViewDesc.Texture2D.MipSlice = 0;

	Device->CreateDepthStencilView(DepthStencilBuffer.Get(), &DepthStencilViewDesc, &DepthStencilView);

    return S_OK;
}

void UDXDDepthStencilView::ReleaseDepthStencilView()
{
	if (DepthStencilBuffer)
	{
		DepthStencilBuffer->Release();
		DepthStencilBuffer.Reset();
	}

	if (DepthStencilView)
	{
		DepthStencilView->Release();
		DepthStencilView.Reset();
	}
}
