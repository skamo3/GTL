#pragma once

#include "Actor.h"

class UCameraComponent;
struct FMatrix;

class ACamera : public AActor
{
public:
	ACamera();

public:
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;

public:
	UCameraComponent* GetCameraComponent() const { return CameraComponent; }


private:
	UCameraComponent* CameraComponent;

};
