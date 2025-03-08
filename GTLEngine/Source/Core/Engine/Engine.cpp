#include "pch.h"
#include "Engine.h"

#include "DirectX11/DirectXHandle.h"

void UEngine::InitEngine()
{
	DirectX11Handle = make_shared<UDirectXHandle>();
	DirectX11Handle->CreateDirectX11Handle();
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

	// DirectX11Handle->Render(World->GetObjects());

}

void UEngine::ClearEngine()
{
	if (DirectX11Handle)
		DirectX11Handle->ReleaseDirectX11Handle();
}
