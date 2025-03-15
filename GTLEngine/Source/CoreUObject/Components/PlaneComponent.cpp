#include "pch.h"
#include "PlaneComponent.h"

UPlaneComponent::UPlaneComponent()
	: UPrimitiveComponent()
{
	PrimitiveType = EPrimitiveType::Plane;
}

void UPlaneComponent::Tick(float TickTime)
{
}

void UPlaneComponent::Destroy()
{
}

FAABB UPlaneComponent::GetAABB() const {
	FVector min = FVector(FLT_MAX, FLT_MAX, FLT_MAX);
	FVector max = FVector(FLT_MIN, FLT_MIN, FLT_MIN);

	/*FVertexSimple TriangleVertices[] = {
		{0.5, -0.5, 0, 1, 0, 0, 1},
		{-0.5, -0.5, 0, 0, 1, 0, 1},
		{0, 0.5, 0, 0, 0, 1, 1},
	};*/

	FVector vecs[3] = {
		FVector(0.5f, -0.5f, 0.f),
		FVector(-0.5f, -0.5f, 0.f),
		FVector(0.f, 0.5f, 0.f),
	};

	FMatrix transform = GetWorldMatrix();
	for ( int i = 0; i < 3; i++ ) {
		vecs[i] = transform.TransformVector(vecs[i]);
		if ( vecs[i].X < min.X ) min.X = vecs[i].X;
		if ( vecs[i].Y < min.Y ) min.Y = vecs[i].Y;
		if ( vecs[i].Z < min.Z ) min.Z = vecs[i].Z;
		if ( vecs[i].X > max.X ) max.X = vecs[i].X;
		if ( vecs[i].Y > max.Y ) max.Y = vecs[i].Y;
		if ( vecs[i].Z > max.Z ) max.Z = vecs[i].Z;
	}

	return FAABB(min, max);
}

bool UPlaneComponent::IsIntersect(FRay ray, float hitDistance, FVector& hitPoint) const {
	FVector vecs[3] = {
		FVector(0.5f, -0.5f, 0.f),
		FVector(-0.5f, -0.5f, 0.f),
		FVector(0.f, 0.5f, 0.f),
	};

	FMatrix transform = GetWorldMatrix();
	for ( int i = 0; i < 3; i++ ) {
		vecs[i] = transform.TransformVector(vecs[i]);
	}
	
	return IsRayIntersectWithTriangle(ray, vecs[0], vecs[1], vecs[2], hitDistance, hitPoint);;
}
