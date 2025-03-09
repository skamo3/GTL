#include "pch.h"
#include "SceneComponent.h"

USceneComponent::USceneComponent()
	: RelativeLocation(FVector::ZeroVector), RelativeRotation(FVector::ZeroVector), RelativeScale3D(FVector::OneVector)
{
	AttachParent = nullptr;
}
