#include "pch.h"
#include "SceneManager.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "Core/Input/InputManager.h"
#include "Utils/Math/Geometry.h"

#include "GameFrameWork/Shapes/Triangle.h"
#include "GameFrameWork/Shapes/Sphere.h"
#include "GameFrameWork/Shapes/Cube.h"
#include "GameFrameWork/Shapes/Cylinder.h"
#include "GameFrameWork/Shapes/Cone.h"
#include "GameFrameWork/Shapes/Line.h"

void USceneManager::DeleteActor(uint32 uuid) {

}

void USceneManager::DeleteActor(FString InName) {

}

void USceneManager::RenderUI() {

    const char* items[] = { "None", "Line", "Triangle", "Sphere", "Cube", "Cylinder", "Cone" };

    if ( SpawnNum < 1 )
        SpawnNum = 1;

	ImGui::Begin("Scene Manager");
	ImGui::DragFloat3("Location", SpawnLocation);
	ImGui::DragFloat3("Rotation", SpawnRotation);
	ImGui::DragFloat3("Scale", SpawnScale);
    ImGui::Combo("Primitive", &CurrentPrimitiveType, items, ARRAYSIZE(items));
    ImGui::InputInt("Number of Spawn", &SpawnNum);
    if (ImGui::Button("Spawn")) {
        for (int i = 0; i < SpawnNum; i++) {
            switch ( static_cast<EPrimitiveType>(CurrentPrimitiveType) ) {
            case EPrimitiveType::Line:
                SpawnActor<ALine>(TEXT("Line"));
                break;
            case EPrimitiveType::Triangle:
                SpawnActor<ATriangle>(TEXT("Triangle"));
                break;
            case EPrimitiveType::Sphere:
                SpawnActor<ASphere>(TEXT("Sphere"));
                break;
            case EPrimitiveType::Cube:
                SpawnActor<ACube>(TEXT("Cube"));
                break;
            case EPrimitiveType::Cylinder:
                SpawnActor<ACylinder>(TEXT("Cylinder"));
                break;
            case EPrimitiveType::Cone:
                SpawnActor<ACone>(TEXT("Cone"));
                break;
            default:
                break;
            }
        }
    }
    ImGui::Separator();
    ImGui::Checkbox("Spawn debug line", &DebugSpawnLine);
    ImGui::Separator();

    // TODO: Insert Actor List
    //ImGui::BeginChild("ScrollingRegion");
    //for (UObject* obj: GUObjectArray) {
    //    if (obj) {
    //        FString ws = obj->GetName();
    //        std::string s;
    //        s.assign(ws.begin(), ws.end());
    //        ImGui::Text("%s(%d)", s.c_str(), obj->GetUUID());
    //    }
    //}
    //ImGui::EndChild();

	ImGui::End();
}

void USceneManager::Tick(float TickTime) {
	RenderUI();

    UInputManager* inputManager = UEngine::GetEngine().GetInputManager();
    if ( DebugSpawnLine && inputManager->GetMouseDown(UInputManager::EMouseButton::LEFT) ) {
		float mouse_x = inputManager->GetMouseNdcX();
		float mouse_y = inputManager->GetMouseNdcY();
		FRay ray = Geometry::CreateRayWithMouse(mouse_x, mouse_y);
		ALine* line = UEngine::GetEngine().GetWorld()->SpawnActor<ALine>(
			TEXT("Line"),
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			FVector::OneVector,
			nullptr
		);
        line->SetRay(ray);
	}
}

void USceneManager::Destroy() {}
