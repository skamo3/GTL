#include "pch.h"
#include "UIManager.h"

#include "Math/Matrix.h"
#include "UI/JungleConsole.h"
#include "UI/JunglePropertyWindow.h"
#include "UI/JungleControlPanel.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"



void UUIManager::Initialize(HWND hWnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplWin32_Init((void*)hWnd);
	ImGui_ImplDX11_Init(device, deviceContext);

	JungleConsole = new UJungleConsole(this);
	JunglePropertyWindow = new UJunglePropertyWindow(this);
	JungleControlPanel = new UJungleControlPanel(this);
}

void UUIManager::Tick(float TickTime)
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	JungleConsole->Tick(TickTime);
	JunglePropertyWindow->Tick(TickTime);
	JungleControlPanel->Tick(TickTime);

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void UUIManager::Destroy()
{
	if (JungleConsole) 
	{
		JungleConsole->Destroy();
		delete JungleConsole;
		JungleConsole = nullptr;
	}

	if (JunglePropertyWindow)
	{
		JunglePropertyWindow->Destroy();
		delete JunglePropertyWindow;
		JunglePropertyWindow = nullptr;
	}

	if (JungleControlPanel) 
	{
		JungleControlPanel->Destroy();
		delete JungleControlPanel;
		JungleControlPanel = nullptr;
	}

	
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

bool UUIManager::GetFPS(int& outFPS)
{
	if (true) {
		// TODO: OutFPS 입력
		outFPS;
		return true;
	}
	return false;
}

bool UUIManager::GetDeltaTime(int& outDeltaTime)
{
	if (true) {
		// TODO: outDeltaTime 입력
		outDeltaTime;
		return true;
	}
	return false;
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


