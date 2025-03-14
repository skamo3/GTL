#include "pch.h"
#include "ControlPanel.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"

#include "Engine.h"

#include "Resource/Types.h"

#include "World.h"
#include "GameFrameWork/Camera.h"
#include "Components/CameraComponent.h"

#include "GameFrameWork/Shapes/Plane.h"
#include "GameFrameWork/Shapes/Sphere.h"
#include "GameFrameWork/Shapes/Cube.h"
#include "GameFrameWork/Shapes/Cylinder.h"
#include "GameFrameWork/Shapes/Cone.h"

UControlPanel::UControlPanel()
	: UUIBase(), CurrentPrimitiveType(0), SpawnNum(1), SceneName("NewScene"), blsOrthogonal(nullptr), Location{ 0.f, 0.f,0.f }, Rotation{ 0.f,0.f,0.f }, 
    FOV(nullptr), CameraLocation(nullptr), CameraRotation(nullptr), WindowWidth(360.f), WindowHeight(400.f), NewScene(false), LoadScene(false), SaveScene(false)
{

}

void UControlPanel::Tick(float DeltaTime)
{
 //   ImGui::Begin("Control Panel");
 //   ImGui::Text("Hello Jungle World!");

 //   // FPS 출력.
 //   DrawFPS();
 //   ImGui::Separator();
	//DrawSpawnPrimitive();
 //   /*
	//	Spawn Primitive,

	//	Save, Load, New Scene,

	//	Camera Setting
	//	Orthogonal,
	//	FOV, Location, Rotation,

 //   */

 //   ImGui::End();
    Render();
}

void UControlPanel::Destroy()
{
}

//void UControlPanel::DrawFPS()
//{
//	ImGui::Text("FPS %.2f", UEngine::GetEngine().GetFPS());
//}
//
//const char* primitives[] = { "Sphere", "Cube", "Plane" }; 
//
//void UControlPanel::DrawSpawnPrimitive()
//{
//	
//	ImGui::PushItemWidth(200);
//	ImGui::Combo("Primitive", &CurrentPrimitiveType, Items, IM_ARRAYSIZE(Items));
//	ImGui::PopItemWidth();
//
//	if (ImGui::Button("Spawn"))
//	{
//		std::cout << "Spawn Actor : " << CurrentPrimitiveType << std::endl;
//
//		UWorld* World = UEngine::GetEngine().GetWorld();
//		if (!World)
//			return;
//
//		// 액터 스폰.
//		switch (static_cast<EPrimitiveType>(CurrentPrimitiveType))
//		{
//		case EPrimitiveType::Plane:
//			World->SpawnActor<APlane>(TEXT("Plane"), FVector(0.f, 0.f, 0.f), FVector(0.f, 0.f, 0.f), FVector::OneVector, nullptr);
//			break;
//		case EPrimitiveType::Sphere:
//			World->SpawnActor<ASphere>(TEXT("Sphere"), FVector(0.f, 0.f, 0.f), FVector(0.f, 0.f, 0.f), FVector::OneVector, nullptr);
//			break;
//		case EPrimitiveType::Cube:
//			World->SpawnActor<ACube>(TEXT("Cube"), FVector(0.f, 0.f, 0.f), FVector(0.f, 0.f, 0.f), FVector::OneVector, nullptr);
//			break;
//		case EPrimitiveType::Cylinder:
//			World->SpawnActor<ACylinder>(TEXT("Cylinder"), FVector(0.f, 0.f, 0.f), FVector(0.f, 0.f, 0.f), FVector::OneVector, nullptr);
//			break;
//		case EPrimitiveType::Cone:
//			World->SpawnActor<ACone>(TEXT("Cone"), FVector(0.f, 0.f, 0.f), FVector(0.f, 0.f, 0.f), FVector::OneVector, nullptr);
//			break;
//		default:
//			break;
//		}
//
//	}
//
//}

void UControlPanel::Render()
{
    ImGuiIO& io = ImGui::GetIO();

    float scaleX = io.DisplaySize.x / 1600.0f;
    float scaleY = io.DisplaySize.y / 900.0f;

    ImVec2 WinSize(WindowWidth * scaleX, WindowHeight * scaleY);

    ImGui::SetNextWindowPos(ImVec2(5, 10), ImGuiCond_Appearing);
    ImGui::SetNextWindowSize(WinSize, ImGuiCond_Appearing);

    ImGui::Begin("Control Panel", nullptr, ImGuiWindowFlags_NoResize);

    ImGui::Text("WILD ENGINE - KRFTON JUNGLE");
    ImGui::Text("FPS %.0f (%.0f ms)", io.Framerate, 1000.0f / io.Framerate);

    ImGui::Separator();

    ImFont* UnicodeFont = io.Fonts->Fonts[FEATHER_FONT];

    ImVec2 ControlButtonSize = ImVec2(32, 32);

    ImGui::PushFont(UnicodeFont);
    ImVec4 ActiveColor = ImVec4(0, 0.5, 0, 0.6f);

    UWorld* World = UEngine::GetEngine().GetWorld();
	if (!World)
		return;

    ACamera* Camera = World->GetCamera();
    UCameraComponent* camera = Camera->GetCameraComponent();


    

    //if (isTranslationActive)
    //    ImGui::PushStyleColor(ImGuiCol_Button, ActiveColor);
    if (ImGui::Button("\ue9bc", ControlButtonSize)); // 기즈모 이동버튼
    //if (isTranslationActive)
    //    ImGui::PopStyleColor();

    ImGui::SameLine(0, 5.0f);

    //bool isRotationActive = (PrimaryGizmo && PrimaryGizmo->GetCurrentGizmo() == EGizmoType::Rotation);
    //if (isRotationActive)
    //    ImGui::PushStyleColor(ImGuiCol_Button, ActiveColor);
    if (ImGui::Button("\ue9d3", ControlButtonSize));
    //if (isRotationActive)
    //    ImGui::PopStyleColor();

    ImGui::SameLine(0, 5.0f);

    //bool isScaleActive = (PrimaryGizmo && PrimaryGizmo->GetCurrentGizmo() == EGizmoType::Scale);
    //if (isScaleActive)
    //    ImGui::PushStyleColor(ImGuiCol_Button, ActiveColor);
    if (ImGui::Button("\ue9ab", ControlButtonSize));
        //if (isScaleActive)
        //    ImGui::PopStyleColor();

    ImGui::SameLine();
    float windowContentWidth = ImGui::GetWindowContentRegionMax().x;

    float buttonsTotalWidth = ControlButtonSize.x * 2 + 5.0f;
    float posX = windowContentWidth - buttonsTotalWidth;
    if (posX < 0)
        posX = 0;

    ImGui::SetCursorPosX(posX);

    if(ImGui::Button("\ue9b7", ControlButtonSize)); // console 창

    ImGui::SameLine(0, 5.0f);

    if(ImGui::Button("\ue918", ControlButtonSize)); // stat 창


    ImGui::PopFont();

    ImGui::Separator();

    ImGui::SetNextItemWidth(100);

    ImGui::Combo("Primitive", &CurrentPrimitiveType, Items, IM_ARRAYSIZE(Items));

    ImGui::SameLine(0, 5.0f);

    if (CreateCustomInputInt("Number Of Spawn", ImGuiDataType_S32, &SpawnNum, "%d", ImGuiInputTextFlags_::ImGuiInputTextFlags_CharsDecimal))

    ImGui::Separator();

    ImGui::PushFont(UnicodeFont);

    NewScene = ImGui::Button("\ue96d", ControlButtonSize); // New Scene

    ImGui::SameLine(0, 5.0f);
    LoadScene = ImGui::Button("\ue950", ControlButtonSize); // Load Scene

    ImGui::SameLine(0, 5.0f);
    SaveScene = ImGui::Button("\ue9d6", ControlButtonSize); // Save Scene


    ImGui::PopFont();

    char buf[20];
    strncpy_s(buf, SceneName.c_str(), sizeof(buf));
    buf[sizeof(buf) - 1] = '\0';

    ImGui::SetNextItemWidth(150);

    if (ImGui::InputText("SceneName", buf, sizeof(buf)))
    {
        SceneName = buf;
    }

    ImGui::Separator();

    //if (ImGui::Checkbox("Orthogonal", blsOrthogonal))
    //{

    //}

    //if (ImGui::DragFloat("FOV", FOV, 1, 0, 120))
    //{

    //}

    ImGui::DragFloat3("Camera Location", Location);


    ImGui::DragFloat3("Camera Rotation", Rotation);


    ImGui::End();
}

bool UControlPanel::CreateCustomInputInt(const char* label, ImGuiDataType data_type, void* p_data, const char* format, ImGuiInputTextFlags flags)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    ImGuiStyle& style = g.Style;
    IM_ASSERT((flags & ImGuiInputTextFlags_EnterReturnsTrue) == 0); // Not supported by InputScalar()!

    if (format == NULL)
        format = ImGui::DataTypeGetInfo(data_type)->PrintFmt;

    void* p_data_default = (g.NextItemData.HasFlags & ImGuiNextItemDataFlags_HasRefVal) ? &g.NextItemData.RefVal : &g.DataTypeZeroValue;

    char buf[64];
    if ((flags & ImGuiInputTextFlags_DisplayEmptyRefVal) && ImGui::DataTypeCompare(data_type, p_data, p_data_default) == 0)
        buf[0] = 0;
    else
        ImGui::DataTypeFormatString(buf, IM_ARRAYSIZE(buf), data_type, p_data, format);

    g.NextItemData.ItemFlags |= ImGuiItemFlags_NoMarkEdited;
    flags |= ImGuiInputTextFlags_AutoSelectAll | (ImGuiInputTextFlags)ImGuiInputTextFlags_LocalizeDecimalPoint;

    bool value_changed = false;
    const float button_size = ImGui::GetFrameHeight();

    ImGui::BeginGroup();
    ImGui::PushID(label);
    ImGui::SetNextItemWidth(ImMax(1.0f, ImGui::CalcItemWidth() - (button_size + style.ItemInnerSpacing.x) * 6 + 15));
    if (ImGui::InputText("", buf, IM_ARRAYSIZE(buf), flags))
        ImGui::DataTypeApplyFromText(buf, data_type, p_data, format, (flags & ImGuiInputTextFlags_ParseEmptyRefVal) ? p_data_default : NULL);
    IMGUI_TEST_ENGINE_ITEM_INFO(g.LastItemData.ID, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Inputable);

    const ImVec2 backup_frame_padding = style.FramePadding;
    style.FramePadding.x = style.FramePadding.y;
    if (flags & ImGuiInputTextFlags_ReadOnly)
        ImGui::BeginDisabled();
    ImGui::PushItemFlag(ImGuiItemFlags_ButtonRepeat, true);
    ImGui::SameLine(0, style.ItemInnerSpacing.x);
    if (ImGui::ButtonEx("Spawn", ImVec2(button_size * 4.2f, button_size)))
    {
        value_changed = true;
    }
    ImGui::PopItemFlag();
    if (flags & ImGuiInputTextFlags_ReadOnly)
        ImGui::EndDisabled();

    style.FramePadding = backup_frame_padding;

    ImGui::PopID();
    ImGui::EndGroup();


    g.LastItemData.ItemFlags &= ~ImGuiItemFlags_NoMarkEdited;
    if (value_changed)
        ImGui::MarkItemEdited(g.LastItemData.ID);

    return value_changed;
}


//void UControlPanel::DrawSpawnPrimitive()
//{
//    ImGui::PushItemWidth(200);
//    ImGui::Combo("Primitive", &currentPrimitive, primitives, IM_ARRAYSIZE(primitives));
//    ImGui::PopItemWidth();
//    if (ImGui::Button("Spawn")) 
//    {
//        UIManager->SpawnPrimitive();
//    }
//    ImGui::SameLine();
//
//    if (spawnNum < 1) spawnNum = 1;
//    // 숫자를 문자열로 변환
//
//    ImGui::PushItemWidth(148);
//    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
//    ImGui::SliderInt("Number of spawn", &spawnNum, 1, 50);
//    ImGui::PopStyleVar();
//    ImGui::PopItemWidth();
//    ImGui::Separator();
//}
//
//void UControlPanel::DrawSceneManage()
//{
//    ImGui::PushItemWidth(200);
//    ImGui::InputText("Scene Name", sceneName, IM_ARRAYSIZE(sceneName));
//    ImGui::PopItemWidth();
//    if (ImGui::Button("New Scene")) 
//    {
//        UIManager->MakeNewScene();
//    }
//    if (ImGui::Button("Save Scene")) 
//    {
//        UIManager->SaveScene(sceneName);
//    }
//    if (ImGui::Button("Load Scene")) 
//    {
//        UIManager->LoadScene(sceneName);
//    }
//    ImGui::Separator();
//}
//
//void UControlPanel::DrawCameraSetting()
//{
//    bool bOrthogonal = false;
//    ImGui::Checkbox("Orthogonal", &bOrthogonal);
//
//    float fovValue = -1.0f;
//    UIManager->GetFOV(fovValue);
//
//    ImGui::PushItemWidth(200);
//    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
//    if (ImGui::SliderFloat("FOV", &fovValue, 0.0f, 90.0f))
//        UIManager->OnFOVChanged(fovValue);
//    ImGui::PopStyleVar();
//    ImGui::PopItemWidth();
//
//    FVector cameraLocation;
//    UIManager->GetCameraLocation(cameraLocation);
//    ImGui::PushItemWidth(67);
//    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
//    bool valueChanged = false;
//    if (ImGui::SliderFloat("##cameraLocationX", &cameraLocation.X, -10.f, 10.f))
//        valueChanged = true;
//    ImGui::SameLine();
//    if (ImGui::SliderFloat("##cameraLocationY", &cameraLocation.Y, -10.f, 10.f))
//        valueChanged = true;
//    ImGui::SameLine();
//    if (ImGui::SliderFloat("##cameraLocationZ", &cameraLocation.Z, -10.f, 10.f))
//        valueChanged = true;
//
//    if (valueChanged)
//        UIManager->OnCameraLocationChanged(cameraLocation);
//    ImGui::SameLine();
//    ImGui::Text("Camera Location");
//    ImGui::PopStyleVar();
//    ImGui::PopItemWidth();
//
//    FVector cameraRotation;
//    UIManager->GetCameraRotation(cameraRotation);
//    ImGui::PushItemWidth(67);
//    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 0.0f);
//    valueChanged = false;
//    if (ImGui::SliderFloat("##cameraRotationX", &cameraRotation.X, -10.f, 10.f))
//        valueChanged = true;
//    ImGui::SameLine();
//    if (ImGui::SliderFloat("##cameraRotationY", &cameraRotation.Y, -10.f, 10.f))
//        valueChanged = true;
//    ImGui::SameLine();
//    if (ImGui::SliderFloat("##cameraRotationZ", &cameraRotation.Z, -10.f, 10.f))
//        valueChanged = true;
//    
//    if (valueChanged)
//        UIManager->OnCameraRotationChanged(cameraRotation);
//
//    ImGui::SameLine();
//    ImGui::Text("Camera Rotation");
//    ImGui::PopStyleVar();
//    ImGui::PopItemWidth();
//
//    ImGui::Separator();
//    ImGui::Spacing();
//    ImGui::Text("Select Gizmo Mode");
//    if (ImGui::Button("Translation", ImVec2(105, 25))) 
//    {
//        UIManager->OnGizmoModeChanged(0);
//    }
//    ImGui::SameLine();
//    if (ImGui::Button("Rotation", ImVec2(105, 25))) 
//    {
//        UIManager->OnGizmoModeChanged(1);
//    }
//    ImGui::SameLine();
//    if (ImGui::Button("Scale", ImVec2(105, 25))) 
//    {
//        UIManager->OnGizmoModeChanged(2);
//    }
//
//}
