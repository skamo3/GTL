#include "pch.h"
#include "JunglePropertyWindow.h"



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
    ImGui::PushItemWidth(67);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
    ImGui::SliderFloat("##objectTranslationX", &objectTranslation.X, -10.f, 10.f, "%.3f");
    ImGui::SameLine();
    ImGui::SliderFloat("##objectTranslationX", &objectTranslation.Y, -10.f, 10.f, "%.3f");
    ImGui::SameLine();
    ImGui::SliderFloat("##objectTranslationX", &objectTranslation.Z, -10.f, 10.f, "%.3f");
    ImGui::SameLine();
    ImGui::Text("Translation");
    ImGui::PopStyleVar();
    ImGui::PopItemWidth();
}

void UJunglePropertyWindow::DrawObjectRotation()
{
    ImGui::PushItemWidth(67);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
    ImGui::SliderFloat("##objectRotationX", &objectRotation.X, -10.f, 10.f, "%.3f");
    ImGui::SameLine();
    ImGui::SliderFloat("##objectRotationY", &objectRotation.Y, -10.f, 10.f, "%.3f");
    ImGui::SameLine();
    ImGui::SliderFloat("##objectRotationZ", &objectRotation.Z, -10.f, 10.f, "%.3f");
    ImGui::SameLine();
    ImGui::Text("Rotation");
    ImGui::PopStyleVar();
    ImGui::PopItemWidth();
}

void UJunglePropertyWindow::DrawObjectScale()
{
    ImGui::PushItemWidth(67);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
    ImGui::SliderFloat("##objectScaleX", &objectScale.X, -10.f, 10.f, "%.3f");
    ImGui::SameLine();
    ImGui::SliderFloat("##objectScaleY", &objectScale.Y, -10.f, 10.f, "%.3f");
    ImGui::SameLine();
    ImGui::SliderFloat("##objectScaleZ", &objectScale.Z, -10.f, 10.f, "%.3f");
    ImGui::SameLine();
    ImGui::Text("Scale");
    ImGui::PopStyleVar();
    ImGui::PopItemWidth();
}


