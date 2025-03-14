#include "pch.h"
#include "ControlPanel.h"

#include "ImGui/imgui.h"

#include "Engine.h"

#include "Resource/Types.h"

#include "World.h"
#include "GameFrameWork/Shapes/Plane.h"
#include "GameFrameWork/Shapes/Sphere.h"
#include "GameFrameWork/Shapes/Cube.h"
#include "GameFrameWork/Shapes/Cylinder.h"
#include "GameFrameWork/Shapes/Cone.h"

UControlPanel::UControlPanel()
	: UUIBase(), CurrentPrimitiveType(0), SpawnNum(1), Location{ 0.f, 0.f, 0.f }
{
}

void UControlPanel::Tick(float DeltaTime)
{
    ImGui::Begin("Control Panel");
    ImGui::Text("Hello Jungle World!");

    // FPS 출력.
    DrawFPS();
    ImGui::Separator();
	DrawSpawnPrimitive();
    /*
		Spawn Primitive,

		Save, Load, New Scene,

		Camera Setting
		Orthogonal,
		FOV, Location, Rotation,

    */

    ImGui::End();
}

void UControlPanel::Destroy()
{
}

void UControlPanel::DrawFPS()
{
	ImGui::Text("FPS %.2f", UEngine::GetEngine().GetFPS());
}

const char* primitives[] = { "Sphere", "Cube", "Plane" }; 

void UControlPanel::DrawSpawnPrimitive()
{
	
	ImGui::PushItemWidth(200);
	ImGui::DragFloat3("Location", Location);
	ImGui::Combo("Primitive", &CurrentPrimitiveType, Items, IM_ARRAYSIZE(Items));
	ImGui::PopItemWidth();

	if (ImGui::Button("Spawn"))
	{
		std::cout << "Spawn Actor : " << CurrentPrimitiveType << std::endl;

		UWorld* World = UEngine::GetEngine().GetWorld();
		if (!World)
			return;

		// 액터 스폰.
		switch (static_cast<EPrimitiveType>(CurrentPrimitiveType))
		{
		case EPrimitiveType::Plane:
			World->SpawnActor<APlane>(TEXT("Plane"), FVector(Location[0], Location[1], Location[2]), FVector(0.f, 0.f, 0.f), FVector::OneVector, nullptr);
			break;
		case EPrimitiveType::Sphere:
			World->SpawnActor<ASphere>(TEXT("Sphere"), FVector(Location[0], Location[1], Location[2]), FVector(0.f, 0.f, 0.f), FVector::OneVector, nullptr);
			break;
		case EPrimitiveType::Cube:
			World->SpawnActor<ACube>(TEXT("Cube"), FVector(Location[0], Location[1], Location[2]), FVector(0.f, 0.f, 0.f), FVector::OneVector, nullptr);
			break;
		case EPrimitiveType::Cylinder:
			World->SpawnActor<ACylinder>(TEXT("Cylinder"), FVector(Location[0], Location[1], Location[2]), FVector(0.f, 0.f, 0.f), FVector::OneVector, nullptr);
			break;
		case EPrimitiveType::Cone:
			World->SpawnActor<ACone>(TEXT("Cone"), FVector(Location[0], Location[1], Location[2]), FVector(0.f, 0.f, 0.f), FVector::OneVector, nullptr);
			break;
		default:
			break;
		}

	}

}


//void UControlPanel::DrawSpawnPrimitive()
//{
//    ImGui::PushItemWidth(200);
//    ImGui::Combo("Primitive", &currentPrimitive, primitives, IM_ARRAYSIZE(primitives));
//    ImGui::PopItemWidth();
//    if (ImGui::Button("Spawn")) 
//    {
//        UIManager->SpawnPrimitive();
//    }
//    ImGui::SameLine();
//
//    if (spawnNum < 1) spawnNum = 1;
//    // 숫자를 문자열로 변환
//
//    ImGui::PushItemWidth(148);
//    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
//    ImGui::SliderInt("Number of spawn", &spawnNum, 1, 50);
//    ImGui::PopStyleVar();
//    ImGui::PopItemWidth();
//    ImGui::Separator();
//}
//
//void UControlPanel::DrawSceneManage()
//{
//    ImGui::PushItemWidth(200);
//    ImGui::InputText("Scene Name", sceneName, IM_ARRAYSIZE(sceneName));
//    ImGui::PopItemWidth();
//    if (ImGui::Button("New Scene")) 
//    {
//        UIManager->MakeNewScene();
//    }
//    if (ImGui::Button("Save Scene")) 
//    {
//        UIManager->SaveScene(sceneName);
//    }
//    if (ImGui::Button("Load Scene")) 
//    {
//        UIManager->LoadScene(sceneName);
//    }
//    ImGui::Separator();
//}
//
//void UControlPanel::DrawCameraSetting()
//{
//    bool bOrthogonal = false;
//    ImGui::Checkbox("Orthogonal", &bOrthogonal);
//
//    float fovValue = -1.0f;
//    UIManager->GetFOV(fovValue);
//
//    ImGui::PushItemWidth(200);
//    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
//    if (ImGui::SliderFloat("FOV", &fovValue, 0.0f, 90.0f))
//        UIManager->OnFOVChanged(fovValue);
//    ImGui::PopStyleVar();
//    ImGui::PopItemWidth();
//
//    FVector cameraLocation;
//    UIManager->GetCameraLocation(cameraLocation);
//    ImGui::PushItemWidth(67);
//    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
//    bool valueChanged = false;
//    if (ImGui::SliderFloat("##cameraLocationX", &cameraLocation.X, -10.f, 10.f))
//        valueChanged = true;
//    ImGui::SameLine();
//    if (ImGui::SliderFloat("##cameraLocationY", &cameraLocation.Y, -10.f, 10.f))
//        valueChanged = true;
//    ImGui::SameLine();
//    if (ImGui::SliderFloat("##cameraLocationZ", &cameraLocation.Z, -10.f, 10.f))
//        valueChanged = true;
//
//    if (valueChanged)
//        UIManager->OnCameraLocationChanged(cameraLocation);
//    ImGui::SameLine();
//    ImGui::Text("Camera Location");
//    ImGui::PopStyleVar();
//    ImGui::PopItemWidth();
//
//    FVector cameraRotation;
//    UIManager->GetCameraRotation(cameraRotation);
//    ImGui::PushItemWidth(67);
//    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
//    valueChanged = false;
//    if (ImGui::SliderFloat("##cameraRotationX", &cameraRotation.X, -10.f, 10.f))
//        valueChanged = true;
//    ImGui::SameLine();
//    if (ImGui::SliderFloat("##cameraRotationY", &cameraRotation.Y, -10.f, 10.f))
//        valueChanged = true;
//    ImGui::SameLine();
//    if (ImGui::SliderFloat("##cameraRotationZ", &cameraRotation.Z, -10.f, 10.f))
//        valueChanged = true;
//    
//    if (valueChanged)
//        UIManager->OnCameraRotationChanged(cameraRotation);
//
//    ImGui::SameLine();
//    ImGui::Text("Camera Rotation");
//    ImGui::PopStyleVar();
//    ImGui::PopItemWidth();
//
//    ImGui::Separator();
//    ImGui::Spacing();
//    ImGui::Text("Select Gizmo Mode");
//    if (ImGui::Button("Translation", ImVec2(105, 25))) 
//    {
//        UIManager->OnGizmoModeChanged(0);
//    }
//    ImGui::SameLine();
//    if (ImGui::Button("Rotation", ImVec2(105, 25))) 
//    {
//        UIManager->OnGizmoModeChanged(1);
//    }
//    ImGui::SameLine();
//    if (ImGui::Button("Scale", ImVec2(105, 25))) 
//    {
//        UIManager->OnGizmoModeChanged(2);
//    }
//
//}
