#include "JungleControlPanel.h"

UJungleControlPanel::UJungleControlPanel()
{
}

UJungleControlPanel::~UJungleControlPanel()
{
}

void UJungleControlPanel::Draw()
{
    ImGui::Begin("Jungle Control Panel");
    ImGui::Text("Hello Jungle World!");
    int fps = 7777;
    int deltaTime = 1;
    ImGui::Text("FPS %d (%d ms)", fps, deltaTime);
    ImGui::Separator();

    // 위쪽에 선언함
    ImGui::PushItemWidth(200);
    ImGui::Combo("Primitive", &currentPrimitive, primitives, IM_ARRAYSIZE(primitives));
    ImGui::PopItemWidth();
    ImGui::Button("Spawn");
    ImGui::SameLine();

    if (spawnNum < 1) spawnNum = 1;
    // 숫자를 문자열로 변환

    strncpy(strOut, uUIManager.ChangeNumToStrWithMargin(10, spawnNum).c_str(), sizeof(strOut) - 1);
    strOut[sizeof(strOut) - 1] = '\0';
    ImGui::PushItemWidth(148);
    ImGui::InputText("Number of spawn", strOut, IM_ARRAYSIZE(strOut));
    spawnNum = atoi(strOut);
    ImGui::PopItemWidth();
    ImGui::Separator();

    ImGui::PushItemWidth(200);
    ImGui::InputText("Scene Name", sceneName, IM_ARRAYSIZE(sceneName));
    ImGui::PopItemWidth();
    ImGui::Button("New Scene");
    ImGui::Button("Save Scene");
    ImGui::Button("Load Scene");

    ImGui::Separator();

    bool bOrthogonal = false;
    ImGui::Checkbox("Orthogonal", &bOrthogonal);

    strncpy(strOut, uUIManager.ChangeNumToStrWithMargin(10, fovValue).c_str(), sizeof(strOut) - 1);
    strOut[sizeof(strOut) - 1] = '\0';
    ImGui::PushItemWidth(200);
    ImGui::InputText("FOV", strOut, IM_ARRAYSIZE(strOut));
    fovValue = atof(strOut);
    ImGui::PopItemWidth();

    ImGui::PushItemWidth(67);
    strncpy(strOut, uUIManager.ChangeNumToStrWithMargin(4, cameraLocation.X).c_str(), sizeof(strOut) - 1);
    strOut[sizeof(strOut) - 1] = '\0';
    ImGui::InputText("##cameraLocationX", strOut, IM_ARRAYSIZE(strOut));
    cameraLocation.X = atof(strOut);
    ImGui::SameLine();
    strncpy(strOut, uUIManager.ChangeNumToStrWithMargin(4, cameraLocation.Y).c_str(), sizeof(strOut) - 1);
    strOut[sizeof(strOut) - 1] = '\0';
    ImGui::InputText("##cameraLocationY", strOut, IM_ARRAYSIZE(strOut));
    cameraLocation.Y = atof(strOut);
    ImGui::SameLine();
    strncpy(strOut, uUIManager.ChangeNumToStrWithMargin(4, cameraLocation.Z).c_str(), sizeof(strOut) - 1);
    strOut[sizeof(strOut) - 1] = '\0';
    ImGui::InputText("##cameraLocationZ", strOut, IM_ARRAYSIZE(strOut));
    cameraLocation.Z = atof(strOut);
    ImGui::SameLine();
    ImGui::Text("Camera Location");
    ImGui::PopItemWidth();


    ImGui::PushItemWidth(67);
    strncpy(strOut, uUIManager.ChangeNumToStrWithMargin(4, cameraRotation.X).c_str(), sizeof(strOut) - 1);
    strOut[sizeof(strOut) - 1] = '\0';
    ImGui::InputText("##cameraRotationX", strOut, IM_ARRAYSIZE(strOut));
    cameraRotation.X = atof(strOut);
    ImGui::SameLine();
    strncpy(strOut, uUIManager.ChangeNumToStrWithMargin(4, cameraRotation.Y).c_str(), sizeof(strOut) - 1);
    strOut[sizeof(strOut) - 1] = '\0';
    ImGui::InputText("##cameraRotationY", strOut, IM_ARRAYSIZE(strOut));
    cameraRotation.Y = atof(strOut);
    ImGui::SameLine();
    strncpy(strOut, uUIManager.ChangeNumToStrWithMargin(4, cameraRotation.Z).c_str(), sizeof(strOut) - 1);
    strOut[sizeof(strOut) - 1] = '\0';
    ImGui::InputText("##cameraRotationZ", strOut, IM_ARRAYSIZE(strOut));
    cameraRotation.Z = atof(strOut);
    ImGui::SameLine();
    ImGui::Text("Camera Rotation");
    ImGui::PopItemWidth();

    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Text("Select Gizmo Mode");
    ImGui::Button("Translation", ImVec2(105, 25));
    ImGui::SameLine();
    ImGui::Button("Rotation", ImVec2(105, 25));
    ImGui::SameLine();
    ImGui::Button("Scale", ImVec2(105, 25));


    ImGui::End();
}

template<typename T>
void UJungleControlPanel::ChangeNumToStrWithMargin(int marginNum, T num)
{
    strncpy(strOut, uUIManager.ChangeNumToStrWithMargin(4, num).c_str(), sizeof(strOut) - 1);
    strOut[sizeof(strOut) - 1] = '\0';
}