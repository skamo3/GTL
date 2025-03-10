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
    int fps, deltaTime;
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
    ImGui::PopItemWidth();
    if (ImGui::Button("Spawn")) 
    {
        UIManager->SpawnPrimitive();
    }
    ImGui::SameLine();

    if (spawnNum < 1) spawnNum = 1;
    // 숫자를 문자열로 변환

    ImGui::PushItemWidth(148);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
    ImGui::SliderInt("Number of spawn", &spawnNum, 1, 50);
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

    float fovValue = -1.0f;
    UIManager->GetFOV(fovValue);

    ImGui::PushItemWidth(200);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
    if (ImGui::SliderFloat("FOV", &fovValue, 0.0f, 90.0f))
        UIManager->OnFOVChanged(fovValue);
    ImGui::PopStyleVar();
    ImGui::PopItemWidth();

    FVector cameraLocation;
    UIManager->GetCameraLocation(cameraLocation);
    ImGui::PushItemWidth(67);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
    bool valueChanged = false;
    if (ImGui::SliderFloat("##cameraLocationX", &cameraLocation.X, -10.f, 10.f))
        valueChanged = true;
    ImGui::SameLine();
    if (ImGui::SliderFloat("##cameraLocationY", &cameraLocation.Y, -10.f, 10.f))
        valueChanged = true;
    ImGui::SameLine();
    if (ImGui::SliderFloat("##cameraLocationZ", &cameraLocation.Z, -10.f, 10.f))
        valueChanged = true;

    if (valueChanged)
        UIManager->OnCameraLocationChanged(cameraLocation);
    ImGui::SameLine();
    ImGui::Text("Camera Location");
    ImGui::PopStyleVar();
    ImGui::PopItemWidth();

    FVector cameraRotation;
    UIManager->GetCameraRotation(cameraRotation);
    ImGui::PushItemWidth(67);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
    valueChanged = false;
    if (ImGui::SliderFloat("##cameraRotationX", &cameraRotation.X, -10.f, 10.f))
        valueChanged = true;
    ImGui::SameLine();
    if (ImGui::SliderFloat("##cameraRotationY", &cameraRotation.Y, -10.f, 10.f))
        valueChanged = true;
    ImGui::SameLine();
    if (ImGui::SliderFloat("##cameraRotationZ", &cameraRotation.Z, -10.f, 10.f))
        valueChanged = true;
    
    if (valueChanged)
        UIManager->OnCameraRotationChanged(cameraRotation);

    ImGui::SameLine();
    ImGui::Text("Camera Rotation");
    ImGui::PopStyleVar();
    ImGui::PopItemWidth();

    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Text("Select Gizmo Mode");
    if (ImGui::Button("Translation", ImVec2(105, 25))) 
    {
        UIManager->OnGizmoModeChanged(0);
    }
    ImGui::SameLine();
    if (ImGui::Button("Rotation", ImVec2(105, 25))) 
    {
        UIManager->OnGizmoModeChanged(1);
    }
    ImGui::SameLine();
    if (ImGui::Button("Scale", ImVec2(105, 25))) 
    {
        UIManager->OnGizmoModeChanged(2);
    }

}
