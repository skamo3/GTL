#include "pch.h"
#include "DirectXHandle.h"

#include "DXDRenderTarget.h"
#include "DXDDepthStencilView.h"
#include "DXDRasterizerState.h"
#include "DXDShaderManager.h"

#include "CoreUObject/GameFrameWork/Actor.h"
#include "CoreUObject/GameFrameWork/Camera.h"

#include "Engine.h"

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
	swapchaindesc.OutputWindow = UEngine::GetEngine().GetWindowInfo().WindowHandle; // 렌더링할 창 핸들
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

HRESULT UDirectXHandle::CreateShaderManager()
{
	ShaderManager = make_shared<UDXDShaderManager>(DXDDevice);
	if (ShaderManager == nullptr)
		return S_FALSE;

	// VertexShader 생성 및 InputLayout 생성.
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	HRESULT hr = ShaderManager->AddVertexShaderAndInputLayout("DefaultVS", "Resource/Shader/ShaderW0.hlsl", layout, ARRAYSIZE(layout));

	hr = ShaderManager->AddPixelShader("DefaultPX", "Resource/Shader/ShaderW0.hlsl");
	if (FAILED(hr))
		return hr;

	return S_OK;
}

HRESULT UDirectXHandle::CreateDirectX11Handle(HWND hWnd)
{
	HRESULT hr;
	// 디바이스 및 스왑체인 생성.
	hr = CreateDeviceAndSwapchain();
	if (FAILED(hr))
		return hr;

	// 래스터라이저 스테이트 생성.
	RasterizerState = make_shared<UDXDRasterizerState>();
	if (RasterizerState == nullptr)
		return S_FALSE;
	hr = RasterizerState->CreateRasterizerState(DXDDevice);
	if (FAILED(hr))
		return hr;

	// 셰이더 초기화. VertexShader, PixelShader, InputLayout 생성.
	// VertexShader, InputLayout 는 쌍으로 생성 및 이름으로 관리.
	hr = CreateShaderManager();
	
	// 뎁스 스텐실 뷰 생성.
	DepthStencilView = make_shared<UDXDDepthStencilView>();
	hr = DepthStencilView->CreateDepthStencilView(DXDDevice, UEngine::GetEngine().GetWindowInfo().WindowHandle);
	if (FAILED(hr))
		return hr;

	return S_OK;
}

void UDirectXHandle::ReleaseDirectX11Handle()
{
	if (DXDDeviceContext)
	{
		DXDDeviceContext->Flush();
		DXDDeviceContext.Reset();
	}

	if (DXDDevice)
	{
		DXDDevice.Reset();
	}

	if (DXDSwapChain)
	{
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

void UDirectXHandle::UpdateCameraMatrix(ACamera* Camera)
{
	// Camera->GetCameraComponent.
	// MVP 계산 행렬 구하고
	// 카메라 상수버퍼로 바로 전달.
}

void UDirectXHandle::RenderObejct(const TArray<AActor*> Actors)
{
	// 그릴 렌더 타겟뷰 초기화.
	InitView();
	// 셰이더 준비.
	// 현재 액터가 가진 Component 타입 별로 분석해서 셰이더 적용.
	// 컴포넌트에서 정보 가져와서 Constant 버퍼 업데이트.
	// 액터에 해당하는 오브젝트 렌더링.


	DXDSwapChain->Present(1, 0);
}

void UDirectXHandle::InitView()
{
	// 렌더 타겟 클리어 및 클리어에 적용할 색.
	FLOAT ClearColor[4] = { 0.25f, 0.25f, 0.25f, 1.0f };

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

HRESULT UDirectXHandle::AddRenderTarget(string TargetName, const D3D11_RENDER_TARGET_VIEW_DESC& RenderTargetViewDesc)
{
	shared_ptr<UDXDRenderTarget> NewRenderTarget = make_shared<UDXDRenderTarget>();
	
	HRESULT hr = NewRenderTarget->CreateRenderTarget(DXDDevice, DXDSwapChain, RenderTargetViewDesc);
	if (FAILED(hr))
		return hr;
	RenderTarget.insert(make_pair(TargetName, NewRenderTarget));

	return S_OK;
}
