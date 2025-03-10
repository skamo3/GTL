#pragma once

#include "CoreUObject/Object.h"
#include "Math/Math.h"

class UActorComponent;
class USceneComponent;
	
class AActor : public UObject
{
public:
	AActor();


public:
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;

public:
	template<typename T>
	T* AddComponent(AActor* Owner, const FVector& InRelativeLocation = FVector::ZeroVector, const FVector& InRelativeRotation = FVector::ZeroVector, const FVector& InRelativeScale = FVector::ZeroVector);

	template<typename T>
	T* GetComponentByClass() const
	{
		T* FoundComponent = nullptr;
		for (UActorComponent* Comp : OwnedComponent)
		{
			if (Comp)
			{
				FoundComponent = dynamic_cast<T>(Comp);
				if (FoundComponent != nullptr)
					return FoundComponent;
			}
		}
		return FoundComponent;
	}

public:
	USceneComponent* GetRootComponent() const { return RootComponent; }
	void SetOwner(AActor* InOwner);

protected:
	USceneComponent* RootComponent;

private:
	AActor* Owner;
	TArray<UActorComponent*> OwnedComponent;

};

template<typename T>
inline T* AActor::AddComponent(AActor* Owner, const FVector& InRelativeLocation, const FVector& InRelativeRotation, const FVector& InRelativeScale)
{
	T* NewComp = new T();
	// ActorComponent 하위 클래스가 아니라면 에러.
	if (dynamic_cast<UActorComponent>(NewComp) == nullptr)
	{
		// "Actor Component 아니라는 에러 메시지 출력. "
		return nullptr;
	}
	USceneComponent* NewSceneComp = dynamic_cast<USceneComponent>(NewComp);
	if (NewSceneComp == nullptr)
	{
		return nullptr;
	}

	if (RootComponent == nullptr)
	{
		RootComponent = NewSceneComp;
	}
	else
	{
		NewSceneComp->SetupAttachment(RootComponent);
	}
	NewSceneComp->SetRelativeLocation(InLocation);
	NewSceneComp->SetRelativeRotation(InRotation);
	NewSceneComp->SetRelativeScale3D(InScale);

	OwnedComponent.push_back(NewComp);
	return NewComp;
}
