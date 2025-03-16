#pragma once

#include "Object.h"
#include "Math/Vector.h"
#include "ImGui/imgui.h"

class UUIBase;
class UGizmoManager;
class IDragable;

class UUIManager : public UObject
{

public:
	void InitUI(const FWindowInfo& WindowInfo, ID3D11Device* DXDDevice, ID3D11DeviceContext* DXDDeviceContext);

	virtual void Tick(float DeltaTime) override;
	virtual void Destroy() override;

	void RegistUI(UUIBase* NewUI);
	void RenderUI();

private:
	TArray<UUIBase*> UIList;
	ImGuiIO* IO;
public:
	inline const bool IsImGuiWantTextInput() const { return IO->WantTextInput; }
	inline const bool IsImGuiWantMouseInput() const { return IO->WantCaptureMouse; }

	// Property Window Function
	bool GetObjectTranslation(FVector& outTranslation);
	void OnObjectTranslationChanged(FVector& inTranslation);

	bool GetObjectRotation(FVector& outRotation);
	void OnObjectRotationChanged(FVector& inRotation);

	bool GetObjectScale(FVector& outScale);
	void OnObjectScaleChanged(FVector& inScale);

	void SpawnPrimitive();

	void MakeNewScene();
	void SaveScene(char* inSceneName);
	void LoadScene(char* inSceneName);

	bool GetFOV(float& outFOV);
	void OnFOVChanged(float& inFOV);

	bool GetCameraLocation(FVector& outLocation);
	void OnCameraLocationChanged(FVector& inLocation);

	bool GetCameraRotation(FVector& outRotation);
	void OnCameraRotationChanged(FVector& inRotation);

	void OnGizmoModeChanged(int modeNum);

	void CreateUsingFont();

	void PreferenceStyle();
public:
	// Console Function

};