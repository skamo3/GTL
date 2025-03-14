#pragma once

#include "Object.h"
#include "Core/Resource/Types.h"

class AActor;

class UActorComponent : public UObject
{

public:
	UActorComponent()
		: UObject()
		, OwnerPrivate(nullptr)
	{
	}

	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;
	virtual FAABB GetAABB();

public:
	inline AActor* GetOwner() const { return OwnerPrivate; }
	inline void SetOwner(AActor* InOwner) { OwnerPrivate = InOwner; }

private:
	AActor* OwnerPrivate;
};