#include "JunglePropertyWindow.h"

UJunglePropertyWindow::UJunglePropertyWindow()
{

}

UJunglePropertyWindow::~UJunglePropertyWindow()
{

}

void UJunglePropertyWindow::Draw()
{
    ImGui::Begin("Jungle Property Window ");

    ImGui::PushItemWidth(67);
    ChangeNumToStrWithMargin(4, objectTranslation.X);
    ImGui::InputText("##objectTranslationX", strOut, IM_ARRAYSIZE(strOut));
    objectTranslation.X = atof(strOut);
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, objectTranslation.Y);
    ImGui::InputText("##objectTranslationY", strOut, IM_ARRAYSIZE(strOut));
    objectTranslation.Y = atof(strOut);
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, objectTranslation.Z);
    ImGui::InputText("##objectTranslationZ", strOut, IM_ARRAYSIZE(strOut));
    objectTranslation.Z = atof(strOut);
    ImGui::SameLine();
    ImGui::Text("Translation");
    ImGui::PopItemWidth();


    ImGui::PushItemWidth(67);
    ChangeNumToStrWithMargin(4, objectRotation.X);
    ImGui::InputText("##objectRotationX", strOut, IM_ARRAYSIZE(strOut));
    objectRotation.X = atof(strOut);
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, objectRotation.Y);
    ImGui::InputText("##objectRotationY", strOut, IM_ARRAYSIZE(strOut));
    objectRotation.Y = atof(strOut);
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, objectRotation.Z);
    ImGui::InputText("##objectRotationZ", strOut, IM_ARRAYSIZE(strOut));
    objectRotation.Z = atof(strOut);
    ImGui::SameLine();
    ImGui::Text("Rotation");
    ImGui::PopItemWidth();


    ImGui::PushItemWidth(67);
    ChangeNumToStrWithMargin(4, objectScale.X);
    ImGui::InputText("##objectScaleX", strOut, IM_ARRAYSIZE(strOut));
    objectScale.X = atof(strOut);
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, objectScale.Y);
    ImGui::InputText("##objectScaleY", strOut, IM_ARRAYSIZE(strOut));
    objectScale.Y = atof(strOut);
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, objectScale.Z);
    ImGui::InputText("##objectScaleZ", strOut, IM_ARRAYSIZE(strOut));
    objectScale.Z = atof(strOut);
    ImGui::SameLine();
    ImGui::Text("Scale");
    ImGui::PopItemWidth();


    ImGui::End();
}

template<typename T>
void UJunglePropertyWindow::ChangeNumToStrWithMargin(int marginNum, T num) {
    strncpy(strOut, uUIManager.ChangeNumToStrWithMargin(4, num).c_str(), sizeof(strOut) - 1);
    strOut[sizeof(strOut) - 1] = '\0';
}
