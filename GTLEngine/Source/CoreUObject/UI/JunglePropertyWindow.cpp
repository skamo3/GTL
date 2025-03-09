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
    ImGui::InputText("##objectTranslationX", strOut, bufSize);
    objectTranslation.X = atof(strOut);
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, objectTranslation.Y);
    ImGui::InputText("##objectTranslationY", strOut, bufSize);
    objectTranslation.Y = atof(strOut);
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, objectTranslation.Z);
    ImGui::InputText("##objectTranslationZ", strOut, bufSize);
    objectTranslation.Z = atof(strOut);
    ImGui::SameLine();
    ImGui::Text("Translation");
    ImGui::PopItemWidth();


    ImGui::PushItemWidth(67);
    ChangeNumToStrWithMargin(4, objectRotation.X);
    ImGui::InputText("##objectRotationX", strOut, bufSize);
    objectRotation.X = atof(strOut);
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, objectRotation.Y);
    ImGui::InputText("##objectRotationY", strOut, bufSize);
    objectRotation.Y = atof(strOut);
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, objectRotation.Z);
    ImGui::InputText("##objectRotationZ", strOut, bufSize);
    objectRotation.Z = atof(strOut);
    ImGui::SameLine();
    ImGui::Text("Rotation");
    ImGui::PopItemWidth();


    ImGui::PushItemWidth(67);
    ChangeNumToStrWithMargin(4, objectScale.X);
    ImGui::InputText("##objectScaleX", strOut, bufSize);
    objectScale.X = atof(strOut);
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, objectScale.Y);
    ImGui::InputText("##objectScaleY", strOut, bufSize);
    objectScale.Y = atof(strOut);
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, objectScale.Z);
    ImGui::InputText("##objectScaleZ", strOut, bufSize);
    objectScale.Z = atof(strOut);
    ImGui::SameLine();
    ImGui::Text("Scale");
    ImGui::PopItemWidth();


    ImGui::End();
}

template<typename T>
void UJunglePropertyWindow::ChangeNumToStrWithMargin(int marginNum, T num) {
    bufSize = uUIManager.ChangeNumToStrWithMargin(4, num).size() + 1;
    strOut = new char[bufSize];
    strncpy(strOut, uUIManager.ChangeNumToStrWithMargin(4, num).c_str(), bufSize);
    strOut[bufSize - 1] = '\0';
}
