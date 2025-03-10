#pragma once

#include "CoreUObject/Object.h"
#include "Math/Math.h"

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

public:
	USceneComponent* GetRootComponent() const { return RootComponent; }
	void SetOwner(AActor* InOwner);

protected:
	USceneComponent* RootComponent;
private:
	AActor* Owner;

};

template<typename T>
inline T* AActor::AddComponent(AActor* Owner, const FVector& InRelativeLocation, const FVector& InRelativeRotation, const FVector& InRelativeScale)
{
	// ActorComponent 하위 클래스가 아니라면 에러.
	T* NewComp = new T();
	USceneComponent* NewSceneComp = dynamic_cast<USceneComponent>(NewComp);
	NewSceneComp->SetRelativeLocation(InLocation);
	NewSceneComp->SetRelativeRotation(InRotation);
	NewSceneComp->SetRelativeScale3D(InScale)
	return NewComp;
}
