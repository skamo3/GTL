#include "pch.h"
#include "Engine.h"

#include "DirectX11/DirectXHandle.h"

uint32 UEngineStatics::NextUUID = 0;

void UEngine::InitEngine(HWND hWnd)
{
	DirectX11Handle = new UDirectXHandle();
	DirectX11Handle->CreateDirectX11Handle(hWnd);
}

void UEngine::Update()
{
	// TimeManager.

	// World 오브젝트 값들 없데이트.
	/*
	
	for (auto Object : World->GetObjects())
	{
		Object->Update();
	}
	
	*/

}

void UEngine::Render()
{
	DirectX11Handle->PrepareRender();

	// 오브젝트들 받아와서 DXD 핸들에 넘겨준 후 DXD 핸들에서 해당 오브젝트 값 읽어서 렌더링에 추가.
	// DirectX11Handle->Render(World->GetObjects());

}

void UEngine::ClearEngine()
{
	if (DirectX11Handle)
		DirectX11Handle->ReleaseDirectX11Handle();
}

