#pragma once

typedef struct FVector;
class UJungleConsole;

class UUIManager {

public:
	void RegisterJungleConsole(UJungleConsole& inJungleConsole);

private:
	UJungleConsole* JungleConsole;

	
public:
	// Property Window Function
	bool GetObjectTranslation(FVector& outTranslation);
	void SetObjectTranslation(FVector& inTranslation);

	bool GetObjectRotation(FVector& outRotation);
	void SetObjectRotation(FVector& inRotation);

	bool GetObjectScale(FVector& outScale);
	void SetObjectScale(FVector& inScale);

public:
	// Control Panel Function
	bool GetFPS(int& outFPS);
	bool GetDeltaTime(int& outDeltaTime);

	void SetPrimitive(int& inPrimitiveNum);

	void SpawnPrimitive();

	bool GetSpawnNum(int& outSpawnNum);
	void SetSpawnNum(int& inSpawnNum);

	void MakeNewScene();
	void SaveScene(char* inSceneName);
	void LoadScene(char* inSceneName);

	bool GetFOV(float& outFOV);
	void SetFOV(float& inFOV);

	bool GetCameraLocation(FVector& outLocation);
	void SetCameraLocation(FVector& inLocation);

	bool GetCameraRotation(FVector& outRotation);
	void SetCameraRotation(FVector& inRotation);

	void ChangeGizmo(int modeNum);

public:
	// Console Function

};