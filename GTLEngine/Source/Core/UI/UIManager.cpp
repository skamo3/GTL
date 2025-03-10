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

void UUIManager::SetObjectTranslation(FVector& inTranslation)
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

void UUIManager::SetObjectRotation(FVector& inRotation)
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

void UUIManager::SetObjectScale(FVector& inScale)
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

void UUIManager::SetPrimitive(int& inPrimitiveNum)
{

}

void UUIManager::SpawnPrimitive()
{

}

bool UUIManager::GetSpawnNum(int& outSpawnNum)
{
	if (true) 
	{
		// TODO: outSpawnNum 입력
		outSpawnNum;
		return true;
	}
	return false;
}

void UUIManager::SetSpawnNum(int& inSpawnNum)
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

void UUIManager::SetFOV(float& inFOV)
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

void UUIManager::SetCameraLocation(FVector& inLocation)
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

void UUIManager::SetCameraRotation(FVector& inRotation)
{

}

void UUIManager::ChangeGizmo(int modeNum)
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


