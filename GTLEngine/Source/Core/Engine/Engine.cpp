#include "pch.h"
#include "Engine.h"

#include "DirectX11/DirectXHandle.h"
#include "Manager/InputManager.h"
#include "Resource/ResourceManager.h"

#include "World.h"
#include "GameFrameWork/Actor.h"
#include "GameFrameWork/Camera.h"

uint32 UEngineStatics::NextUUID = 0;

bool UEngine::InitEngine(const FWindowInfo& InWindowInfo)
{
	WindowInfo = InWindowInfo;
	DirectX11Handle = new UDirectXHandle();
	HRESULT hr = DirectX11Handle->CreateDirectX11Handle(WindowInfo.WindowHandle);
	if (FAILED(hr))
	{
		MessageBox(WindowInfo.WindowHandle, L"DirectX11 핸들 생성 실패", L"에러", MB_OK);
		return false;
	}

	D3D11_RENDER_TARGET_VIEW_DESC framebufferRTVdesc = {};
	framebufferRTVdesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB; // 색상 포맷
	framebufferRTVdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D; // 2D 텍스처

	hr = DirectX11Handle->AddRenderTarget(L"MainRenderTarget", framebufferRTVdesc);
	if (FAILED(hr))
	{
		MessageBox(WindowInfo.WindowHandle, L"렌더 타겟 추가 실패", L"에러", MB_OK);
		return false;
	}

	// 셰이더 추가.

    // 리소스 매니저 추가.

    // 월드 추가.
	World = UWorld::CreateWorld(L"MainWorld");

    // 인풋 매니저 추가.
    InputManager = new UInputManager();

	return true;
}

void UEngine::Tick()
{
	// TimeManager.

	// InputManager.

	// World 오브젝트 값들 없데이트.
	World->CameraTick(0.3f);
	World->Tick(0.3f); // TODO: TickTime 값 수정 필요.

}

void UEngine::Render()
{
	DirectX11Handle->UpdateCameraMatrix(MainCamera);
	// 오브젝트들 받아와서 DXD 핸들에 넘겨준 후 DXD 핸들에서 해당 오브젝트 값 읽어서 렌더링에 추가.
	DirectX11Handle->Render(World->GetActors());
}

void UEngine::ClearEngine()
{
	if (DirectX11Handle)
	{
		DirectX11Handle->ReleaseDirectX11Handle();
	}

	if (ResourceManager)
	{
        delete ResourceManager;
		ResourceManager = nullptr;
	}

    if (World)
    {
        delete World;
		World = nullptr;
    }

    if (InputManager)
    {
        delete InputManager;
		InputManager = nullptr;
    }
}

void UEngine::AddTotalAllocationBytes(uint32 Bytes)
{
	TotalAllocationBytes += Bytes;
}

void UEngine::AddTotalAllocationCount(uint32 Count)
{
	TotalAllocationCount += Count;
}

void UEngine::RemoveTotalAllocationBytes(uint32 Bytes)
{
	TotalAllocationBytes -= Bytes;
}

void UEngine::RemoveTotalAllocationCount(uint32 Count)
{
	TotalAllocationCount -= Count;
}
