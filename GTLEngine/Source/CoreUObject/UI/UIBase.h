#pragma once
#include "CoreUObject/Object.h"

class UUIManager;

class UUIBase : public UObject
{
public:
	UUIBase() = delete;

	explicit UUIBase(UUIManager* InUIManager)
		: UIManager(InUIManager)
	{
	}

public:
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;

	virtual void Draw() = 0;

protected:
	UUIManager* UIManager;
};