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

	FMatrix GetViewMatrix() const;
	FMatrix GetProjectionMatrix(float width, float height) const;

private:
	UCameraComponent* CameraComponent;

};
