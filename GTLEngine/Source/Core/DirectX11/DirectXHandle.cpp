#include "pch.h"
#include "DirectXHandle.h"

#include "DXDDevice.h"
#include "DXDSwapChain.h"
#include "DXDRenderTarget.h"
#include "DXDDepthStencilView.h"
#include "DXDRasterizerState.h"

UDirectXHandle::~UDirectXHandle()
{
	ReleaseDirectX11Handle();
}

HRESULT UDirectXHandle::CreateDirectX11Handle()
{
	DXDDevice = make_shared<UDXDDevice>();
	HRESULT hr = DXDDevice->CreateDeviceAndContext();
	if (FAILED(hr)) 
		return hr;

	SwapChain = make_shared<UDXDSwapChain>();
	SwapChain->CreateSwapChain(WindowInfo.hWnd, DXDDevice, ViewportInfo);

	RenderTarget = make_shared<UDXDRenderTarget>();
	RenderTarget->CreateRenderTarget(DXDDevice, SwapChain);

	RasterizerState = make_shared<UDXDRasterizerState>();
	RasterizerState->CreateRasterizerState(DXDDevice);

	return S_OK;
}

void UDirectXHandle::ReleaseDirectX11Handle()
{
	DXDDevice->ReleaseDeviceAndContext();
	SwapChain->ReleaseSwapChain();
	RenderTarget->ReleaseRenderTarget();

	//ShaderManager();
}

void UDirectXHandle::PrepareRender()
{
	ComPtr<ID3D11DeviceContext> DeviceContext = DXDDevice->GetDeviceContext();

	// 렌더 타겟 클리어 및 클리어에 적용할 색.
	FLOAT ClearColor[4] = { 0.025f, 0.025f, 0.025f, 1.0f };
	DeviceContext->ClearRenderTargetView(RenderTarget->GetFrameBufferRTV().Get(), ClearColor);

	// 뎁스/스텐실 뷰 클리어. 뷰, DEPTH만 클리어, 깊이 버퍼 클리어 할 값, 스텐실 버퍼 클리어 할 값.
	DeviceContext->ClearDepthStencilView(DepthStencilView->GetDepthStencilView().Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DeviceContext->RSSetViewports(1, &ViewportInfo);
	DeviceContext->RSSetState(RasterizerState->GetRasterizerState().Get());

	DeviceContext->OMSetRenderTargets(1, &RenderTarget->GetFrameBufferRTV(), DepthStencilView->GetDepthStencilView().Get());

}
