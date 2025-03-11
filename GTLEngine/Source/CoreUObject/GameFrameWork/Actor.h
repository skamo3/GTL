#pragma once

#include "CoreUObject/Object.h"
#include "Math/Math.h"
#include "CoreUObject/Components/SceneComponent.h"

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
	T* AddComponent(AActor* Owner, const FVector& InRelativeLocation = FVector::ZeroVector, const FVector& InRelativeRotation = FVector::ZeroVector, const FVector& InRelativeScale = FVector::OneVector);

	template<typename T>
	T* GetComponentByClass() const
	{
		T* FoundComponent = nullptr;
		for (UActorComponent* Comp : OwnedComponent)
		{
			if (Comp == nullptr)
			{
				continue;
			}

			FoundComponent = dynamic_cast<T*>(Comp);
			if (FoundComponent != nullptr)
			{
				return FoundComponent;
			}
		}
		return FoundComponent;
	}

public:
	USceneComponent* GetRootComponent() const { return RootComponent; }
	void SetOwner(AActor* InOwner);

	FVector GetActorLocation() const;
	FVector GetActorRotation() const;
	FVector GetActorScale() const;

	void SetActorLocation(FVector InLocation);
	void SetActorRotation(FVector InRotation);
	void SetActorScale(FVector InScale);

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
	UActorComponent* NewActorComp = dynamic_cast<UActorComponent*>(NewComp);
	if (dynamic_cast<UActorComponent*>(NewComp) == nullptr)
	{
		// "Actor Component 아니라는 에러 메시지 출력. "
		return nullptr;
	}
	NewActorComp->SetOwner(Owner);

	USceneComponent* NewSceneComp = dynamic_cast<USceneComponent*>(NewComp);
	if (NewSceneComp == nullptr)
	{
		return nullptr;
	}

	if (RootComponent == nullptr)
	{
		RootComponent = NewSceneComp;
		NewSceneComp->SetName(TEXT("RootComponent"));
	}
	else
	{
		NewSceneComp->SetupAttachment(RootComponent);
	}
	NewSceneComp->SetRelativeLocation(InRelativeLocation);
	NewSceneComp->SetRelativeRotation(InRelativeRotation);
	NewSceneComp->SetRelativeScale(InRelativeScale);

	OwnedComponent.push_back(NewComp);
	return NewComp;
}
