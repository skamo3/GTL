#include "pch.h"
#include "UIManager.h"

#include "Math/Matrix.h"
#include "UI/JungleConsole.h"


void UUIManager::RegisterJungleConsole(UJungleConsole& inJungleConsole)
{
	JungleConsole = &inJungleConsole;
}



bool UUIManager::GetObjectTranslation(FVector& outTranslation)
{
	if (true) {
		// TODO: Translation 대입
		outTranslation;
		return true;
	}

	return false;
}

void UUIManager::OnObjectTranslationChanged(FVector& inTranslation)
{

}

bool UUIManager::GetObjectRotation(FVector& outRotation)
{
	if (true) {
		// TODO: OuRotation 대입
		outRotation;
		return true;
	}

	return false;
}

void UUIManager::OnObjectRotationChanged(FVector& inRotation)
{

}

bool UUIManager::GetObjectScale(FVector& outScale)
{
	if (true) {
		// TODO: OutScale 대입
		outScale;
		return true;
	}
	return false;
}

void UUIManager::OnObjectScaleChanged(FVector& inScale)
{

}

bool UUIManager::GetFPS(int& outFPS)
{
	if (true) {
		// TODO: OutFPS 입력
		outFPS;
		return true;
	}
	return false;
}

bool UUIManager::GetDeltaTime(int& outDeltaTime)
{
	if (true) {
		// TODO: outDeltaTime 입력
		outDeltaTime;
		return true;
	}
	return false;
}


void UUIManager::SpawnPrimitive()
{

}


void UUIManager::MakeNewScene()
{

}

void UUIManager::SaveScene(char* inSceneName)
{

}

void UUIManager::LoadScene(char* inSceneName)
{

}

bool UUIManager::GetFOV(float& outFOV)
{
	if (true) 
	{
		// TODO outFOV 입력
		outFOV;
		return true;
	}
	return false;
}

void UUIManager::OnFOVChanged(float& inFOV)
{
	
}

bool UUIManager::GetCameraLocation(FVector& outLocation)
{
	if (true) 
	{
		// TODO: outLocation 입력
		outLocation;
		return true;
	}
	return false;
}

void UUIManager::OnCameraLocationChanged(FVector& inLocation)
{
}

bool UUIManager::GetCameraRotation(FVector& outRotation)
{
	if (true) 
	{
		// TODO: outRotation 입력
		outRotation;
		return true;
	}
	return false;
}

void UUIManager::OnCameraRotationChanged(FVector& inRotation)
{

}

void UUIManager::OnGizmoModeChanged(int modeNum)
{
	switch (modeNum) {
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}
}


