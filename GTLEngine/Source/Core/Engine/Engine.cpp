#include "pch.h"
#include "Engine.h"

#include "DirectX11/DirectXHandle.h"
#include "Time/TimeManager.h"
#include "Input/InputManager.h"
#include "Resource/ResourceManager.h"
#include "Asset/AssetManager.h"

#include "World.h"
#include "GameFrameWork/Actor.h"
#include "Gizmo/Gizmo.h"

uint32 UEngineStatics::NextUUID = 0;

bool UEngine::InitEngine(const FWindowInfo& InWindowInfo)
{
    WindowInfo = InWindowInfo;

    // 리소스 매니저 추가.
    ResourceManager = new UResourceManager();

    DirectX11Handle = new UDirectXHandle();
    HRESULT hr = DirectX11Handle->CreateDirectX11Handle(WindowInfo.WindowHandle);
    if (FAILED(hr))
    {
        MessageBox(WindowInfo.WindowHandle, TEXT("DirectX11 핸들 생성 실패"), TEXT("Error"), MB_OK);
        return false;
    }

    D3D11_RENDER_TARGET_VIEW_DESC framebufferRTVdesc = {};
    framebufferRTVdesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB; // 색상 포맷
    framebufferRTVdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D; // 2D 텍스처

    hr = DirectX11Handle->AddRenderTarget(TEXT("MainRenderTarget"), framebufferRTVdesc);
    if (FAILED(hr))
    {
        MessageBox(WindowInfo.WindowHandle, TEXT("렌더 타겟 추가 실패"), TEXT("Error"), MB_OK);
        return false;
    }

    // 셰이더 추가.

    // 버텍스 버퍼 추가.
    hr = AddAllPrimitiveVertexBuffers();
    if (FAILED(hr))
    {
        MessageBox(WindowInfo.WindowHandle, TEXT("버텍스 버퍼 생성 실패"), TEXT("Error"), MB_OK);
        return false;
    }

	UAssetManager* AssetManager = new UAssetManager();
	AssetManager->RegistryAssetMetaDatas();
	AssetManager->LoadAssets();

    // 월드 추가.
    World = UWorld::CreateWorld();

	// TimeManager 추가
	TimeManager = new UTimeManager();
	TimeManager->Initialize();

    // 인풋 매니저 추가.
    InputManager = new UInputManager();

    return true;
}

void UEngine::Tick()
{
    // TimeManager.
    TimeManager->Update();

	// InputManager.
    InputManager->Tick(TimeManager->DeltaTime());

    // World 오브젝트 값들 없데이트.
    World->CameraTick(TimeManager->DeltaTime());
    World->Tick(TimeManager->DeltaTime());
}

void UEngine::Render()
{
    DirectX11Handle->UpdateCameraMatrix(World->GetCamera());
    // 오브젝트들 받아와서 DXD 핸들에 넘겨준 후 DXD 핸들에서 해당 오브젝트 값 읽어서 렌더링에 추가.
    DirectX11Handle->RenderGizmo(SelectedObject, Gizmo);
    DirectX11Handle->RenderObejct(World->GetActors());

    // TODO: Draw Line
    DirectX11Handle->DrawLine(Lines);
}

void UEngine::ClearEngine()
{
    if (DirectX11Handle)
    {
        DirectX11Handle->ReleaseDirectX11Handle();
    }

    if (World)
    {
        delete World;
        World = nullptr;
    }

    if (ResourceManager)
    {
        delete ResourceManager;
        ResourceManager = nullptr;
    }

    if (InputManager)
    {
        delete InputManager;
        InputManager = nullptr;
    }

	if (TimeManager) 
	{
		delete TimeManager;
		TimeManager = nullptr;
	}
}

HRESULT UEngine::AddAllPrimitiveVertexBuffers()
{
    HRESULT hr = S_OK;
    for (uint32 i = 0; i < static_cast<uint32>(EPrimitiveType::Max); ++i)
    {
        EPrimitiveType Type = static_cast<EPrimitiveType>(i);
        if (Type != EPrimitiveType::None)
        {
            hr = DirectX11Handle->AddVertexBuffer(Type, *ResourceManager->GetVertexData(Type));
            if (FAILED(hr))
            {
                return hr;
            }
        }
    }
    
    return S_OK;
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
