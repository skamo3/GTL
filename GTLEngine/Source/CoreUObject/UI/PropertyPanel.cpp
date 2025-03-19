#include "pch.h"
#include "PropertyPanel.h"

#include "ImGui/imgui.h"
#include "UI/UIManager.h"
#include "Gizmo/GizmoBase.h"
#include "Utils/Math/Vector.h"
#include "Engine.h"

UPropertyPanel::UPropertyPanel()
	:UUIBase(), WindowWidth(280.f), WindowHeight(360.f)
{
	gizmoManager = UEngine::GetEngine().GetGizmoManager();
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

	AActor* selected = gizmoManager->GetSelected();

	if (selected) {
		Location[0] = selected->GetActorLocation().X;
		Location[1] = selected->GetActorLocation().Y;
		Location[2] = selected->GetActorLocation().Z;
		ImGui::DragFloat3("Location", Location);
		selected->SetActorLocation(FVector(Location[0], Location[1], Location[2]));

		Rotation[0] = selected->GetActorRotation().Euler().X;
		Rotation[1] = selected->GetActorRotation().Euler().Y;
		Rotation[2] = selected->GetActorRotation().Euler().Z;
		ImGui::DragFloat3("Rotation", Rotation);
		selected->SetActorRotation(FRotator(Rotation[1], Rotation[2], Rotation[0]));

		Scale[0] = selected->GetActorScale().X;
		Scale[1] = selected->GetActorScale().Y;
		Scale[2] = selected->GetActorScale().Z;
		ImGui::DragFloat3("Scale", Scale);
		selected->SetActorScale(FVector(Scale[0], Scale[1], Scale[2]));

		ImGui::Text("GUID : %d", selected->GetUUID());
	}

	ImGui::Separator();

	ImGui::Checkbox("WorldCoord", &UGizmoBase::IsAbsoluteCoord);
	ImGui::End();
}