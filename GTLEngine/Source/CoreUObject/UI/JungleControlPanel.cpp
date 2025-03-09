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

    ChangeNumToStrWithMargin(10, spawnNum);
    ImGui::PushItemWidth(148);
    ImGui::InputText("Number of spawn", strOut, bufSize);
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

    ChangeNumToStrWithMargin(10, fovValue);
    ImGui::PushItemWidth(200);
    ImGui::InputText("FOV", strOut, bufSize);
    fovValue = atof(strOut);
    ImGui::PopItemWidth();

    ImGui::PushItemWidth(67);
    ChangeNumToStrWithMargin(4, cameraLocation.X);
    ImGui::InputText("##cameraLocationX", strOut, bufSize);
    cameraLocation.X = atof(strOut);
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, cameraLocation.Y);
    ImGui::InputText("##cameraLocationY", strOut, bufSize);
    cameraLocation.Y = atof(strOut);
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, cameraLocation.Z);
    ImGui::InputText("##cameraLocationZ", strOut, bufSize);
    cameraLocation.Z = atof(strOut);
    ImGui::SameLine();
    ImGui::Text("Camera Location");
    ImGui::PopItemWidth();


    ImGui::PushItemWidth(67);
    ChangeNumToStrWithMargin(4, cameraRotation.X);
    ImGui::InputText("##cameraRotationX", strOut, bufSize);
    cameraRotation.X = atof(strOut);
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, cameraRotation.Y);
    ImGui::InputText("##cameraRotationY", strOut, bufSize);
    cameraRotation.Y = atof(strOut);
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, cameraRotation.Z);
    ImGui::InputText("##cameraRotationZ", strOut, bufSize);
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
    bufSize = uUIManager.ChangeNumToStrWithMargin(4, num).size() + 1;
    strOut = new char[bufSize];
    strncpy(strOut, uUIManager.ChangeNumToStrWithMargin(4, num).c_str(), bufSize);
    strOut[bufSize - 1] = '\0';
}