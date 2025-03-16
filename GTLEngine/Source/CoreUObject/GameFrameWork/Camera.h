#pragma once

#include "Actor.h"

class UCameraComponent;
struct FMatrix;

class ACamera : public AActor
{
public:
	ACamera();
public:
	float MouseSensitive;
public:
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;

public:
	UCameraComponent* GetCameraComponent() const { return CameraComponent; }

	float GetFieldOfView() const;
	float GetNearClip() const;
	float GetFarClip() const;

private:
	UCameraComponent* CameraComponent;
};
