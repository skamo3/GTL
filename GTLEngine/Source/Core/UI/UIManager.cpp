#include "pch.h"
#include "UIManager.h"

#include "Math/Matrix.h"
#include "UI/UIBase.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

void UUIManager::InitUI(const FWindowInfo& WindowInfo, ID3D11Device* DXDDevice, ID3D11DeviceContext* DXDDeviceContext)
{
	// ImGui 생성.
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& IO = ImGui::GetIO();

	ImGui_ImplWin32_Init((void*)WindowInfo.WindowHandle);
	ImGui_ImplDX11_Init(DXDDevice, DXDDeviceContext);

}

void UUIManager::RegistUI(UUIBase* NewUI)
{
	UIList.push_back(NewUI);
}

void UUIManager::Tick(float DeltaTime)
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (UUIBase* UI : UIList)
	{
		if (UI)
		{
			UI->Tick(DeltaTime);
		}
	}

}

void UUIManager::RenderUI()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void UUIManager::Destroy()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

bool UUIManager::GetObjectTranslation(FVector& outTranslation)
{
	if (true) {
		// TODO: Translation 대입
		outTranslation;
		return true;
	}

	return false;
}

void UUIManager::OnObjectTranslationChanged(FVector& inTranslation)
{

}

bool UUIManager::GetObjectRotation(FVector& outRotation)
{
	if (true) {
		// TODO: OuRotation 대입
		outRotation;
		return true;
	}

	return false;
}

void UUIManager::OnObjectRotationChanged(FVector& inRotation)
{

}

bool UUIManager::GetObjectScale(FVector& outScale)
{
	if (true) {
		// TODO: OutScale 대입
		outScale;
		return true;
	}
	return false;
}

void UUIManager::OnObjectScaleChanged(FVector& inScale)
{

}

void UUIManager::SpawnPrimitive()
{

}


void UUIManager::MakeNewScene()
{

}

void UUIManager::SaveScene(char* inSceneName)
{

}

void UUIManager::LoadScene(char* inSceneName)
{

}

bool UUIManager::GetFOV(float& outFOV)
{
	if (true) 
	{
		// TODO outFOV 입력
		outFOV;
		return true;
	}
	return false;
}

void UUIManager::OnFOVChanged(float& inFOV)
{
	
}

bool UUIManager::GetCameraLocation(FVector& outLocation)
{
	if (true) 
	{
		// TODO: outLocation 입력
		outLocation;
		return true;
	}
	return false;
}

void UUIManager::OnCameraLocationChanged(FVector& inLocation)
{
}

bool UUIManager::GetCameraRotation(FVector& outRotation)
{
	if (true) 
	{
		// TODO: outRotation 입력
		outRotation;
		return true;
	}
	return false;
}

void UUIManager::OnCameraRotationChanged(FVector& inRotation)
{

}

void UUIManager::OnGizmoModeChanged(int modeNum)
{
	switch (modeNum) {
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}
}


