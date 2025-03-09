#pragma once

#include "ActorComponent.h"
#include "Math/Math.h"

class USceneComponent : public UActorComponent
{
public:
	USceneComponent();

private:
	FVector RelativeLocation;
	FVector RelativeRotation;
	FVector RelativeScale3D;

public:
	USceneComponent* GetAttachParent() const { return AttachParent; }
	

private:
	USceneComponent* AttachParent;
	TArray<USceneComponent*> AttachChildren;

};