#include "pch.h"
#include "JungleControlPanel.h"

#include "ImGui/imgui.h"
#include "UI/UIManager.h"

UJungleControlPanel::UJungleControlPanel(UUIManager* InUIManager) : UUIBase(InUIManager)
{
    
}

void UJungleControlPanel::Destroy()
{
    UUIBase::Destroy();
}

void UJungleControlPanel::Draw()
{
    ImGui::Begin("Jungle Control Panel");
    ImGui::Text("Hello Jungle World!");


    DrawFPS();
    DrawSpawnPrimitive();
    DrawSceneManage();
    DrawCameraSetting();


    ImGui::End();
}

void UJungleControlPanel::DrawFPS()
{
    if (UIManager->GetFPS(fps) && UIManager->GetDeltaTime(deltaTime)) 
    {
        ImGui::Text("FPS %d (%d ms)", fps, deltaTime);
    }
    else
    {
        ImGui::Text("FPS OR DeltaTime Error");
    }
    
    ImGui::Separator();
}

void UJungleControlPanel::DrawSpawnPrimitive()
{
    ImGui::PushItemWidth(200);
    ImGui::Combo("Primitive", &currentPrimitive, primitives, IM_ARRAYSIZE(primitives));
    UIManager->SetPrimitive(currentPrimitive);
    ImGui::PopItemWidth();
    if (ImGui::Button("Spawn")) 
    {
        UIManager->SpawnPrimitive();
    }
    ImGui::SameLine();

    UIManager->GetSpawnNum(spawnNum);
    if (spawnNum < 1) spawnNum = 1;
    // 숫자를 문자열로 변환

    ImGui::PushItemWidth(148);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
    ImGui::SliderInt("Number of spawn", &spawnNum, 1, 50);
    UIManager->SetSpawnNum(spawnNum);
    ImGui::PopStyleVar();
    ImGui::PopItemWidth();
    ImGui::Separator();
}

void UJungleControlPanel::DrawSceneManage()
{
    ImGui::PushItemWidth(200);
    ImGui::InputText("Scene Name", sceneName, IM_ARRAYSIZE(sceneName));
    ImGui::PopItemWidth();
    if (ImGui::Button("New Scene")) 
    {
        UIManager->MakeNewScene();
    }
    if (ImGui::Button("Save Scene")) 
    {
        UIManager->SaveScene(sceneName);
    }
    if (ImGui::Button("Load Scene")) 
    {
        UIManager->LoadScene(sceneName);
    }
    ImGui::Separator();
}

void UJungleControlPanel::DrawCameraSetting()
{
    bool bOrthogonal = false;
    ImGui::Checkbox("Orthogonal", &bOrthogonal);

    UIManager->GetFOV(fovValue);

    ImGui::PushItemWidth(200);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
    ImGui::SliderFloat("FOV", &fovValue, 0.0f, 90.0f);
    UIManager->SetFOV(fovValue);
    ImGui::PopStyleVar();
    ImGui::PopItemWidth();


    UIManager->GetCameraLocation(cameraLocation);
    ImGui::PushItemWidth(67);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
    ImGui::SliderFloat("##cameraLocationX", &cameraLocation.X, -10.f, 10.f);
    ImGui::SameLine();
    ImGui::SliderFloat("##cameraLocationY", &cameraLocation.Y, -10.f, 10.f);
    ImGui::SameLine();
    ImGui::SliderFloat("##cameraLocationZ", &cameraLocation.Z, -10.f, 10.f);
    UIManager->SetCameraLocation(cameraLocation);
    ImGui::SameLine();
    ImGui::Text("Camera Location");
    ImGui::PopStyleVar();
    ImGui::PopItemWidth();


    UIManager->GetCameraRotation(cameraRotation);
    ImGui::PushItemWidth(67);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
    ImGui::SliderFloat("##cameraRotationX", &cameraRotation.X, -10.f, 10.f);
    ImGui::SameLine();
    ImGui::SliderFloat("##cameraRotationY", &cameraRotation.Y, -10.f, 10.f);
    ImGui::SameLine();
    ImGui::SliderFloat("##cameraRotationZ", &cameraRotation.Z, -10.f, 10.f);
    UIManager->SetCameraRotation(cameraRotation);
    ImGui::SameLine();
    ImGui::Text("Camera Rotation");
    ImGui::PopStyleVar();
    ImGui::PopItemWidth();

    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Text("Select Gizmo Mode");
    if (ImGui::Button("Translation", ImVec2(105, 25))) 
    {
        UIManager->ChangeGizmo(0);
    }
    ImGui::SameLine();
    if (ImGui::Button("Rotation", ImVec2(105, 25))) 
    {
        UIManager->ChangeGizmo(1);
    }
    ImGui::SameLine();
    if (ImGui::Button("Scale", ImVec2(105, 25))) 
    {
        UIManager->ChangeGizmo(2);
    }

}
