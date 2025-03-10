#include "pch.h"
#include "UIBase.h"

#include "UI/UIManager.h"
#include "Utils/JungleLog.h"

#include "ImGui/imgui.h"
#include "ImGuiStringLibrary.h"


void UUIBase::Tick(float TickTime)
{
	Draw();
}

void UUIBase::Destroy()
{

}
