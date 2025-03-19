#include "pch.h"
#include "SceneManager.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "Core/Input/InputManager.h"
#include "Core/Gizmo/GizmoManager.h"
#include "CoreUObject/GameFrameWork/Camera.h"
#include "Utils/Math/Geometry.h"

#include "GameFrameWork/Shapes/Triangle.h"
#include "GameFrameWork/Shapes/Sphere.h"
#include "GameFrameWork/Shapes/Cube.h"
#include "GameFrameWork/Shapes/Cylinder.h"
#include "GameFrameWork/Shapes/Cone.h"
#include "GameFrameWork/Shapes/Line.h"

#include <functional>

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
    ImGui::Checkbox("Spawn debug ray", &DebugSpawnLine);
    ImGui::Separator();

    ImGui::Checkbox("Show Actor List", &bShowActorList);
    if (bShowActorList)
        ShowActorList();

	ImGui::End();
}

void USceneManager::ShowActorList() {
    ImGui::BeginChild("ScrollingRegion");

    // create node for child
    std::function<void(USceneComponent*)> createNode = [&createNode](USceneComponent* comp)->void {
        FString ws = comp->GetName();
        std::string s;
        s.assign(ws.begin(), ws.end());

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
        if ( comp->GetAllChildren().size() == 0 )
            flags |= ImGuiTreeNodeFlags_Leaf;

        if ( ImGui::TreeNodeEx(s.c_str(), flags) ) {
            for ( auto& child : comp->GetAllChildren() ) {
                createNode(child);
            }
            ImGui::TreePop();
        }
    };

    auto setSelected = [](AActor* actor)->void {
        UEngine::GetEngine().GetGizmoManager()->ClearSelected();

        if ( dynamic_cast<ACamera*>(actor) )
            return;
        if ( actor->IsSelected == false ) {
            actor->IsSelected = true;
            UEngine::GetEngine().GetGizmoManager()->SetSelected(actor);
            UEngine::GetEngine().GetGizmoManager()->AttachGizmo(actor);
        } else {
            actor->IsSelected = false;
        }
    };

    for ( AActor* obj : UEngine::GetEngine().GetWorld()->GetActors() ) {
        if ( obj ) {
            FString ws = obj->GetName();
            std::string s;
            s.assign(ws.begin(), ws.end());

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
            if ( obj->IsSelected )
                flags |= ImGuiTreeNodeFlags_Selected;

            bool isOpen = ImGui::TreeNodeEx(s.c_str(), flags);
            if ( ImGui::IsItemClicked() ) {
                setSelected(obj);
            }
            if ( isOpen ) {
                createNode(obj->GetRootComponent());
                ImGui::TreePop();
            }
        }
    }
    ImGui::EndChild();
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
