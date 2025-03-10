#include "pch.h"
#include "JunglePropertyWindow.h"

#include "ImGui/imgui.h"
#include "UI/UIManager.h"

UJunglePropertyWindow::UJunglePropertyWindow(UUIManager* InUIManager) : UUIBase(InUIManager)
{

}

void UJunglePropertyWindow::Destroy()
{
    UUIBase::Destroy();
}

void UJunglePropertyWindow::Draw()
{
    ImGui::Begin("Jungle Property Window ");

    DrawObjectTranslation();
    DrawObjectRotation();
    DrawObjectScale();

    ImGui::End();
}

void UJunglePropertyWindow::DrawObjectTranslation()
{
    std::string strFormat = "%.3f";
    if (UIManager->GetObjectTranslation(objectTranslation))
    {
        strFormat = "-";
    }
    ImGui::PushItemWidth(67);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
    ImGui::SliderFloat("##objectTranslationX", &objectTranslation.X, -10.f, 10.f, strFormat.c_str());
    ImGui::SameLine();
    ImGui::SliderFloat("##objectTranslationX", &objectTranslation.Y, -10.f, 10.f, strFormat.c_str());
    ImGui::SameLine();
    ImGui::SliderFloat("##objectTranslationX", &objectTranslation.Z, -10.f, 10.f, strFormat.c_str());
    ImGui::SameLine();
    ImGui::Text("Translation");
    ImGui::PopStyleVar();
    ImGui::PopItemWidth();
}

void UJunglePropertyWindow::DrawObjectRotation()
{
    std::string strFormat = "%.3f";
    if (UIManager->GetObjectRotation(objectRotation))
    {
        strFormat = "-";
    }
    ImGui::PushItemWidth(67);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
    ImGui::SliderFloat("##objectRotationX", &objectRotation.X, -10.f, 10.f, strFormat.c_str());
    ImGui::SameLine();
    ImGui::SliderFloat("##objectRotationY", &objectRotation.Y, -10.f, 10.f, strFormat.c_str());
    ImGui::SameLine();
    ImGui::SliderFloat("##objectRotationZ", &objectRotation.Z, -10.f, 10.f, strFormat.c_str());
    ImGui::SameLine();
    ImGui::Text("Rotation");
    ImGui::PopStyleVar();
    ImGui::PopItemWidth();
}

void UJunglePropertyWindow::DrawObjectScale()
{
    std::string strFormat = "%.3f";
    if (UIManager->GetObjectScale(objectScale))
    {
        strFormat = "-";
    }
    ImGui::PushItemWidth(67);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
    ImGui::SliderFloat("##objectScaleX", &objectScale.X, -10.f, 10.f, strFormat.c_str());
    ImGui::SameLine();
    ImGui::SliderFloat("##objectScaleY", &objectScale.Y, -10.f, 10.f, strFormat.c_str());
    ImGui::SameLine();
    ImGui::SliderFloat("##objectScaleZ", &objectScale.Z, -10.f, 10.f, strFormat.c_str());
    ImGui::SameLine();
    ImGui::Text("Scale");
    ImGui::PopStyleVar();
    ImGui::PopItemWidth();
}


