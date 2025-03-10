#include "pch.h"
#include "JunglePropertyWindow.h"

#include "ImGui/imgui.h"
#include "UI/UIManager.h"
#include "Utils/Math/Vector.h"

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
    FVector objectTranslation;
    std::string strFormat = "%.3f";
    if (UIManager->GetObjectTranslation(objectTranslation))
    {
        strFormat = "-";
    }
    ImGui::PushItemWidth(67);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);

    bool valueChanged = false;
    if (ImGui::SliderFloat("##objectTranslationX", &objectTranslation.X, -10.f, 10.f, strFormat.c_str()))
        valueChanged = true;
    ImGui::SameLine();
    if (ImGui::SliderFloat("##objectTranslationX", &objectTranslation.Y, -10.f, 10.f, strFormat.c_str()))
        valueChanged = true;
    ImGui::SameLine();
    if (ImGui::SliderFloat("##objectTranslationX", &objectTranslation.Z, -10.f, 10.f, strFormat.c_str()))
        valueChanged = true;
    ImGui::SameLine();

    if (valueChanged)
        UIManager->OnObjectTranslationChanged(objectTranslation);

    ImGui::Text("Translation");
    ImGui::PopStyleVar();
    ImGui::PopItemWidth();
}

void UJunglePropertyWindow::DrawObjectRotation()
{
    FVector objectRotation;
    std::string strFormat = "%.3f";
    if (UIManager->GetObjectRotation(objectRotation))
    {
        strFormat = "-";
    }
    ImGui::PushItemWidth(67);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);

    bool valueChanged = false;
    if (ImGui::SliderFloat("##objectRotationX", &objectRotation.X, -10.f, 10.f, strFormat.c_str()))
        valueChanged = true;
    ImGui::SameLine();
    if (ImGui::SliderFloat("##objectRotationY", &objectRotation.Y, -10.f, 10.f, strFormat.c_str()))
        valueChanged = true;
    ImGui::SameLine();
    if (ImGui::SliderFloat("##objectRotationZ", &objectRotation.Z, -10.f, 10.f, strFormat.c_str()))
        valueChanged = true;
    ImGui::SameLine();

    if (valueChanged)
        UIManager->OnObjectRotationChanged(objectRotation);

    ImGui::Text("Rotation");
    ImGui::PopStyleVar();
    ImGui::PopItemWidth();
}

void UJunglePropertyWindow::DrawObjectScale()
{
    FVector objectScale;
    std::string strFormat = "%.3f";
    if (UIManager->GetObjectScale(objectScale))
    {
        strFormat = "-";
    }
    ImGui::PushItemWidth(67);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);

    bool valueChanged = false;
    if (ImGui::SliderFloat("##objectScaleX", &objectScale.X, -10.f, 10.f, strFormat.c_str()))
        valueChanged = true;
    ImGui::SameLine();
    if (ImGui::SliderFloat("##objectScaleY", &objectScale.Y, -10.f, 10.f, strFormat.c_str()))
        valueChanged = true;
    ImGui::SameLine();
    if (ImGui::SliderFloat("##objectScaleZ", &objectScale.Z, -10.f, 10.f, strFormat.c_str()))
        valueChanged = true;
    ImGui::SameLine();

    if (valueChanged)
        UIManager->OnObjectScaleChanged(objectScale);

    ImGui::Text("Scale");
    ImGui::PopStyleVar();
    ImGui::PopItemWidth();
}


