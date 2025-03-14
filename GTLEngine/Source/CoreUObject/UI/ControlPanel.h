#pragma once

#include "Math/Vector.h"
#include "UI/UIBase.h"


static const char* Items[] = {  "None", "Line", "Plane", "Sphere", "Cube", "Cylinder", "Cone" };

class UControlPanel: public UUIBase
{
public:
	UControlPanel();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void Destroy() override;

private:
	void DrawFPS();
	void DrawSpawnPrimitive();

	void Render();

	bool CreateCustomInputInt(const char* label, ImGuiDataType data_type, void* p_data, const char* format, ImGuiInputTextFlags flags);

private:
	int32 CurrentPrimitiveType;
	uint32 SpawnNum;
	FString SceneName;

	bool* blsOrthogonal;

	float* FOV;
	FVector* CameraLocation;
	FVector* CameraRotation;

	float Location[3];
	float Rotation[3];

	float WindowWidth;
	float WindowHeight;

	bool NewScene;
	bool LoadScene;
	bool SaveScene;
};
