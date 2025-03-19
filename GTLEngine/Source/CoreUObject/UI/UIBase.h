#pragma once
#include "CoreUObject/Object.h"
#include "ImGui/imgui.h"

#define DEFAULT_FONT		0
#define	FEATHER_FONT		1
class UUIManager;

class UUIBase : public UObject
{
public:
	virtual void Tick(float TickTime) = 0;
	virtual void Destroy() = 0;

};