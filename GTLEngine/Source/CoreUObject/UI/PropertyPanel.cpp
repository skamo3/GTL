#include "pch.h"
#include "PropertyPanel.h"

#include "ImGui/imgui.h"
#include "UI/UIManager.h"
#include "Utils/Math/Vector.h"

UPropertyPanel::UPropertyPanel()
	:UUIBase(), WindowWidth(280.f), WindowHeight(360.f)
{
}

void UPropertyPanel::Tick(float DeltaTime)
{
	Render();
}

void UPropertyPanel::Destroy()
{
}

void UPropertyPanel::Render()
{
	ImGuiIO& io = ImGui::GetIO();

	float scaleX = io.DisplaySize.x / 1600.0f;
	float scaleY = io.DisplaySize.y / 900.0f;

	ImVec2 WinSize(WindowWidth * scaleX, WindowHeight * scaleY);

	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - WinSize.x - 5, 10), ImGuiCond_Once);
	ImGui::SetNextWindowSize(WinSize, ImGuiCond_Appearing);
	ImGui::Begin("Property Panel", nullptr, ImGuiWindowFlags_NoResize);

	ImGui::DragFloat3("Location", Location);

	ImGui::DragFloat3("Rotation", Rotation);

	ImGui::DragFloat3("Scale", Scale);

	ImGui::Text("GUID : %d", UUID);

	ImGui::Separator();
	ImGui::End();
}