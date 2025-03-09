#include "pch.h"
#include "SceneComponent.h"

USceneComponent::USceneComponent()
	: RelativeLocation(FVector::ZeroVector), RelativeRotation(FVector::ZeroVector), RelativeScale3D(FVector::OneVector)
{
	AttachParent = nullptr;
}

void USceneComponent::Destroy()
{
	for (USceneComponent* Child : AttachChildren)
	{
		if (Child)
		{
			Child->Destroy();
			delete Child;
			Child = nullptr;
		}
	}
}

void USceneComponent::SetRelativeLocation(const FVector& Loc)
{
	RelativeLocation = Loc;
}

void USceneComponent::SetRelativeRotation(const FVector& Rot)
{
	RelativeRotation = Rot;
}

void USceneComponent::SetRelativeScale3D(const FVector& Scale)
{
	RelativeScale3D = Scale;
}

void USceneComponent::SetupAttachment(USceneComponent* InParent)
{
	AttachParent = InParent;
}
