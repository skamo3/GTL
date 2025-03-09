#include "pch.h"
#include "Engine.h"

#include "DirectX11/DirectXHandle.h"

#include "World.h"
#include "GameFrameWork/Actor.h"

uint32 UEngineStatics::NextUUID = 0;

bool UEngine::InitEngine(HWND hWnd)
{
	DirectX11Handle = new UDirectXHandle();
	HRESULT hr = DirectX11Handle->CreateDirectX11Handle(hWnd);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"DirectX11 핸들 생성 실패", L"에러", MB_OK);
		return false;
	}

	D3D11_RENDER_TARGET_VIEW_DESC framebufferRTVdesc = {};
	framebufferRTVdesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB; // 색상 포맷
	framebufferRTVdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D; // 2D 텍스처

	hr = DirectX11Handle->AddRenderTarget("MainRenderTarget", framebufferRTVdesc);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"렌더 타겟 추가 실패", L"에러", MB_OK);
		return false;
	}

	// 셰이더 추가.

	return true;
}

void UEngine::Update()
{
	// TimeManager.

	// World 오브젝트 값들 없데이트.
	World->Update(0.3f); // TODO: TickTime 값 수정 필요.

}

void UEngine::Render()
{
	
	// 오브젝트들 받아와서 DXD 핸들에 넘겨준 후 DXD 핸들에서 해당 오브젝트 값 읽어서 렌더링에 추가.
	DirectX11Handle->Render(World->GetObjects());

}

void UEngine::ClearEngine()
{
	if (DirectX11Handle)
		DirectX11Handle->ReleaseDirectX11Handle();
}

