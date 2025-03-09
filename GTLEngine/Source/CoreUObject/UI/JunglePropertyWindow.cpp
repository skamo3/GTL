#include "pch.h"
#include "JunglePropertyWindow.h"

// ImGui include.
#include "ImGui/imgui.h"

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
    objectTranslation.X = static_cast<float>(atof(strOut));
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, objectTranslation.Y);
    ImGui::InputText("##objectTranslationY", strOut, bufSize);
    objectTranslation.Y = static_cast<float>(atof(strOut));
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, objectTranslation.Z);
    ImGui::InputText("##objectTranslationZ", strOut, bufSize);
    objectTranslation.Z = static_cast<float>(atof(strOut));
    ImGui::SameLine();
    ImGui::Text("Translation");
    ImGui::PopItemWidth();


    ImGui::PushItemWidth(67);
    ChangeNumToStrWithMargin(4, objectRotation.X);
    ImGui::InputText("##objectRotationX", strOut, bufSize);
    objectRotation.X = static_cast<float>(atof(strOut));
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, objectRotation.Y);
    ImGui::InputText("##objectRotationY", strOut, bufSize);
    objectRotation.Y = static_cast<float>(atof(strOut));
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, objectRotation.Z);
    ImGui::InputText("##objectRotationZ", strOut, bufSize);
    objectRotation.Z = static_cast<float>(atof(strOut));
    ImGui::SameLine();
    ImGui::Text("Rotation");
    ImGui::PopItemWidth();


    ImGui::PushItemWidth(67);
    ChangeNumToStrWithMargin(4, objectScale.X);
    ImGui::InputText("##objectScaleX", strOut, bufSize);
    objectScale.X = static_cast<float>(atof(strOut));
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, objectScale.Y);
    ImGui::InputText("##objectScaleY", strOut, bufSize);
    objectScale.Y = static_cast<float>(atof(strOut));
    ImGui::SameLine();
    ChangeNumToStrWithMargin(4, objectScale.Z);
    ImGui::InputText("##objectScaleZ", strOut, bufSize);
    objectScale.Z = static_cast<float>(static_cast<float>(atof(strOut)));
    ImGui::SameLine();
    ImGui::Text("Scale");
    ImGui::PopItemWidth();


    ImGui::End();
}

