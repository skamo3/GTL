#include "pch.h"
#include "SceneManager.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"

#include "GameFrameWork/Shapes/Triangle.h"
#include "GameFrameWork/Shapes/Sphere.h"
#include "GameFrameWork/Shapes/Cube.h"
#include "GameFrameWork/Shapes/Cylinder.h"
#include "GameFrameWork/Shapes/Cone.h"

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
}

void USceneManager::Destroy() {}
