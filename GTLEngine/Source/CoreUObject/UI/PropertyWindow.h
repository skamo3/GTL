#pragma once

#include "UI/UIBase.h"

class UPropertyWindow: public UUIBase
{
public:
	
	virtual void Tick(float DeltaTime) override;
	virtual void Destroy() override;

};
