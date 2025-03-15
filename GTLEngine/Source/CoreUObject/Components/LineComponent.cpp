#include "pch.h"
#include "LineComponent.h"

ULineComponent::ULineComponent() {
	PrimitiveType = EPrimitiveType::Line;
}

void ULineComponent::Tick(float TickTime) {}

void ULineComponent::Destroy() {}

FAABB ULineComponent::GetAABB() const {
	FVector min, max;
	FMatrix transformation = GetWorldMatrix();
	FVector start = transformation.TransformVector(FVector::Zero());
	FVector end = transformation.TransformVector(FVector(1.0f, 0.f, 0.f));

	min.X = (start.X < end.X) ? start.X : end.X;
	min.Y = (start.Y < end.Y) ? start.Y : end.Y;
	min.Z = (start.Z < end.Z) ? start.Z : end.Z;
	max.X = (start.X > end.X) ? start.X : end.X;
	max.Y = (start.Y > end.Y) ? start.Y : end.Y;
	max.Z = (start.Z > end.Z) ? start.Z : end.Z;
	return FAABB(min, max);
}

bool ULineComponent::IsRayIntersect(FRay ray, float hitDistance, FVector& hitPoint) const {
	return false;
}

FMatrix ULineComponent::GetWorldMatrix() const {
	FMatrix ScaleMat = FMatrix::GetScaleMatrix(GetComponentScale());
	FMatrix RotMat = rotation;
	//FMatrix RotMat = FMatrix::GetRotateMatrix(GetComponentRotation());
	FMatrix TransMat = FMatrix::GetTranslateMatrix(GetComponentLocation());

	FMatrix RotTrs = RotMat * TransMat;
	USceneComponent* Parent = GetParent();
	while ( Parent != nullptr ) {
		FMatrix ParScaleMat = FMatrix::GetScaleMatrix(Parent->GetComponentScale());
		FMatrix ParRotMat = FMatrix::GetRotateMatrix(Parent->GetComponentRotation());
		FMatrix ParTransMat = FMatrix::GetTranslateMatrix(Parent->GetComponentLocation());

		ScaleMat = ScaleMat * ParScaleMat;

		FMatrix RTTemp = ParRotMat * ParTransMat;
		RotTrs = RotTrs * RTTemp;
		Parent = Parent->GetParent();
	}
	return ScaleMat * RotMat * TransMat;
}
