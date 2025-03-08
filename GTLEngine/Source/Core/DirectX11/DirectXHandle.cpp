#include "pch.h"
#include "DirectXHandle.h"

#include "DXDRenderTarget.h"
#include "DXDDepthStencilView.h"
#include "DXDRasterizerState.h"
#include "DXDShaderManager.h"
#include "DXDInputLayout.h"

UDirectXHandle::~UDirectXHandle()
{
	ReleaseDirectX11Handle();
}

HRESULT UDirectXHandle::CreateDeviceAndSwapchain()
{
	D3D_FEATURE_LEVEL FeatureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

	DXGI_SWAP_CHAIN_DESC swapchaindesc = {};
	swapchaindesc.BufferDesc.Width = 0; // 창 크기에 맞게 자동으로 설정
	swapchaindesc.BufferDesc.Height = 0; // 창 크기에 맞게 자동으로 설정
	swapchaindesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // 색상 포맷
	swapchaindesc.SampleDesc.Count = 1; // 멀티 샘플링 비활성화
	swapchaindesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 렌더 타겟으로 사용
	swapchaindesc.BufferCount = 2; // 더블 버퍼링
	swapchaindesc.OutputWindow = WindowHandle; // 렌더링할 창 핸들
	swapchaindesc.Windowed = TRUE; // 창 모드
	swapchaindesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // 스왑 방식

	uint CreateDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG;

	// Direct3D 장치와 스왑 체인을 생성
	HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, CreateDeviceFlags, FeatureLevels, ARRAYSIZE(FeatureLevels), D3D11_SDK_VERSION, &swapchaindesc, &DXDSwapChain, &DXDDevice, nullptr, &DXDDeviceContext);

	if (FAILED(hr))
		return hr;

	// 생성된 스왑 체인의 정보 가져오기
	DXDSwapChain->GetDesc(&swapchaindesc);

	// 뷰포트 정보 설정
	ViewportInfo = { 0.0f, 0.0f, (float)swapchaindesc.BufferDesc.Width, (float)swapchaindesc.BufferDesc.Height, 0.0f, 1.0f };

	return S_OK;
}

HRESULT UDirectXHandle::CreateDirectX11Handle(HWND hWnd)
{
	WindowHandle = hWnd;
	HRESULT hr;
	hr = CreateDeviceAndSwapchain();
	if (FAILED(hr))
		return hr;

	RasterizerState = make_shared<UDXDRasterizerState>();
	if (RasterizerState == nullptr)
		return S_FALSE;
	hr = RasterizerState->CreateRasterizerState(DXDDevice);
	if (FAILED(hr))
		return hr;

	// 셰이더 생성
	ShaderManager = make_shared<UDXDShaderManager>(DXDDevice);
	if (ShaderManager == nullptr)
		return S_FALSE;
	InputLayout = make_shared<UDXDInputLayout>();
	if (InputLayout == nullptr)
		return S_FALSE;

	ComPtr<ID3DBlob> VertexShaderBlob;
	hr = ShaderManager->AddVertexShader("SimpleVertexShader.hlsl", VertexShaderBlob);
	if (FAILED(hr))
		return hr;

	// 이 위로 VertexShader 추가 생성
	hr = InputLayout->CreateInputLayout(DXDDevice, VertexShaderBlob); // Blob은 마지막 최종 Blob으로 저장. 대신 InputLayout은 동일하게 맞춰주어야 함.
	if (FAILED(hr))
		return hr;

	hr = ShaderManager->AddPixelShader("SimplePixelShader.hlsl");
	if (FAILED(hr))
		return hr;

	hr = DepthStencilView->CreateDepthStencilView(DXDDevice);
	if (FAILED(hr))
		return hr;


	return S_OK;
}

void UDirectXHandle::ReleaseDirectX11Handle()
{
	if (DXDDeviceContext)
	{
		DXDDeviceContext->Flush();
		DXDDeviceContext->Release();
		DXDDeviceContext.Reset();
	}

	if (DXDDevice)
	{
		DXDDevice->Release();
		DXDDevice.Reset();
	}

	if (DXDSwapChain)
	{
		DXDSwapChain->Release();
		DXDSwapChain.Reset();
	}


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
	// 렌더 타겟 클리어 및 클리어에 적용할 색.
	FLOAT ClearColor[4] = { 0.025f, 0.025f, 0.025f, 1.0f };

	for (auto& Target : RenderTarget)
	{
		DXDDeviceContext->ClearRenderTargetView(Target.second->GetFrameBufferRTV().Get(), ClearColor);
	}

	// 뎁스/스텐실 뷰 클리어. 뷰, DEPTH만 클리어, 깊이 버퍼 클리어 할 값, 스텐실 버퍼 클리어 할 값.
	DXDDeviceContext->ClearDepthStencilView(DepthStencilView->GetDepthStencilView().Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

	DXDDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DXDDeviceContext->RSSetViewports(1, &ViewportInfo);
	DXDDeviceContext->RSSetState(RasterizerState->GetRasterizerState().Get());

	for (auto& Target : RenderTarget)
	{
		DXDDeviceContext->OMSetRenderTargets(1, &Target.second->GetFrameBufferRTV(), DepthStencilView->GetDepthStencilView().Get());
	}

	DXDDeviceContext->OMSetBlendState(nullptr, nullptr, 0xffffffff);
}

void UDirectXHandle::AddRenderTarget(string TargetName, const D3D11_RENDER_TARGET_VIEW_DESC& RenderTargetViewDesc)
{
	shared_ptr<UDXDRenderTarget> NewRenderTarget = make_shared<UDXDRenderTarget>();
	NewRenderTarget->CreateRenderTarget(DXDDevice, DXDSwapChain, RenderTargetViewDesc);
	RenderTarget.insert(make_pair(TargetName, NewRenderTarget));
}
