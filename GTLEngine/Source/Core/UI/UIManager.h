#pragma once

#include "Math/Vector.h"
class UJungleConsole;
class UJunglePropertyWindow;
class UJungleControlPanel;

class UUIManager {

public:
	void Initialize(HWND hWnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void Tick(float TickTime);
	void Destroy();

private:
	UJungleConsole* JungleConsole;
	UJunglePropertyWindow* JunglePropertyWindow;
	UJungleControlPanel* JungleControlPanel;

	
public:
	// Property Window Function
	bool GetObjectTranslation(FVector& outTranslation);
	void OnObjectTranslationChanged(FVector& inTranslation);

	bool GetObjectRotation(FVector& outRotation);
	void OnObjectRotationChanged(FVector& inRotation);

	bool GetObjectScale(FVector& outScale);
	void OnObjectScaleChanged(FVector& inScale);

public:
	// Control Panel Function
	bool GetFPS(int& outFPS);
	bool GetDeltaTime(int& outDeltaTime);

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

public:
	// Console Function

};