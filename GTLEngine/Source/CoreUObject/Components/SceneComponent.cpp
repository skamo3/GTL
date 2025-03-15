#include "pch.h"
#include "SceneComponent.h"

USceneComponent::USceneComponent()
	: UActorComponent()
	, RelativeLocation(FVector::ZeroVector), RelativeRotation(FVector::ZeroVector), RelativeScale(FVector::OneVector)
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

void USceneComponent::SetRelativeRotation(const FRotator& Rot)
{
	RelativeRotation = Rot;
}

void USceneComponent::SetRelativeScale(const FVector& Scale)
{
	RelativeScale = Scale;
}

void USceneComponent::SetupAttachment(USceneComponent* InParent)
{
	if (AttachParent != nullptr)
	{
		AttachParent->AttachChildren.erase(std::remove(AttachParent->AttachChildren.begin(), AttachParent->AttachChildren.end(), this), AttachParent->AttachChildren.end());
		AttachParent = nullptr;
	}

	if (InParent != AttachParent)
	{
		AttachParent = InParent;
		InParent->AttachChildren.push_back(this);
	}
}