#pragma once

#include "Object.h"

#include "Math/Math.h"

class AActor;

class UWorld : public UObject
{

public:
	static UWorld* CreateWorld(std::wstring WorldName);

	template<typename T>
	T* SpawnActor(std::wstring InName, FVector InLocation, FVector InScale, float InRotation, UObject* InOwner)
	{
		T* newObj = T();
		AActor* newActor = dynamic_pointer_cast<AActor>(newObj);
		// newActor-> SetLocation, SetScale, SetRotation.
		newActor->SetLocation(InLocation);
		newActor->SetScale(InScale);
		newActor->SetRotation(InRotation);

		if (newActor != nullptr)
		{
			newActor->SetOwner(InOwner);
			ActiveActors.push_back(newActor);
		}
		return newObj;
	}

public:
	void CameraTick(float TickTime);
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;



public:
	TArray<AActor*> GetActors() const { return ActiveActors; }

private:
	TArray<AActor*> ActiveActors;

};

