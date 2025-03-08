#include "pch.h"
#include "DirectXHandle.h"

#include "DXDDevice.h"
#include "DXDSwapChain.h"
#include "DXDRenderTarget.h"
#include "DXDDepthStencilView.h"
#include "DXDRasterizerState.h"
#include "DXDShaderManager.h"
#include "DXDInputLayout.h"

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

	RasterizerState = make_shared<UDXDRasterizerState>();
	RasterizerState->CreateRasterizerState(DXDDevice);

	// 셰이더 생성
	ShaderManager = make_shared<UDXDShaderManager>(DXDDevice);
	InputLayout = make_shared<UDXDInputLayout>();

	ComPtr<ID3DBlob> VertexShaderBlob;
	ShaderManager->AddVertexShader("SimpleVertexShader.hlsl", VertexShaderBlob);
	// 이 위로 VertexShader 추가 생성
	InputLayout->CreateInputLayout(DXDDevice, VertexShaderBlob); // Blob은 마지막 최종 Blob으로 저장. 대신 InputLayout은 동일하게 맞춰주어야 함.
	ShaderManager->AddPixelShader("SimplePixelShader.hlsl");

	return S_OK;
}

void UDirectXHandle::ReleaseDirectX11Handle()
{
	DXDDevice->ReleaseDeviceAndContext();
	SwapChain->ReleaseSwapChain();

	for (auto Target : RenderTarget)
	{
		if (Target.second)
			Target.second->ReleaseRenderTarget();
	}
	RenderTarget.clear();

	ShaderManager->ReleaseAllShader();
}

void UDirectXHandle::PrepareRender()
{
	ComPtr<ID3D11DeviceContext> DeviceContext = DXDDevice->GetDeviceContext();

	// 렌더 타겟 클리어 및 클리어에 적용할 색.
	FLOAT ClearColor[4] = { 0.025f, 0.025f, 0.025f, 1.0f };

	for (auto& Target : RenderTarget)
	{
		DeviceContext->ClearRenderTargetView(Target.second->GetFrameBufferRTV().Get(), ClearColor);
	}

	// 뎁스/스텐실 뷰 클리어. 뷰, DEPTH만 클리어, 깊이 버퍼 클리어 할 값, 스텐실 버퍼 클리어 할 값.
	DeviceContext->ClearDepthStencilView(DepthStencilView->GetDepthStencilView().Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DeviceContext->RSSetViewports(1, &ViewportInfo);
	DeviceContext->RSSetState(RasterizerState->GetRasterizerState().Get());

	for (auto& Target : RenderTarget)
	{
		DeviceContext->OMSetRenderTargets(1, &Target.second->GetFrameBufferRTV(), DepthStencilView->GetDepthStencilView().Get());
	}

	DeviceContext->OMSetBlendState(nullptr, nullptr, 0xffffffff);
}

void UDirectXHandle::AddRenderTarget(string TargetName, const D3D11_RENDER_TARGET_VIEW_DESC& RenderTargetViewDesc)
{
	shared_ptr<UDXDRenderTarget> NewRenderTarget = make_shared<UDXDRenderTarget>();
	NewRenderTarget->CreateRenderTarget(DXDDevice, SwapChain, RenderTargetViewDesc);
	RenderTarget.insert(make_pair(TargetName, NewRenderTarget));
}
