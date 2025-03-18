#pragma once
#include "CoreUObject/Object.h"
#include "ImGui/imgui.h"

#define DEFAULT_FONT		0
#define	FEATHER_FONT		1

class UUIBase : public UObject
{
	DECLARE_CLASS(UUIBase, UObject)
public:
	UUIBase() {}

	virtual void Tick(float TickTime);
	virtual void Destroy();

};