#include "pch.h"
#include "CubeComponent.h"

#include "Resource/Types.h"
#include "Utils/Math/Geometry.h"

UCubeComponent::UCubeComponent()
	: UPrimitiveComponent()
{
	PrimitiveType = EPrimitiveType::Cube;
}

void UCubeComponent::Tick(float TickTime)
{

}

void UCubeComponent::Destroy()
{
}

FAABB UCubeComponent::GetAABB() const {
	FVector min = FVector(FLT_MAX, FLT_MAX, FLT_MAX);
	FVector max = FVector(FLT_MIN, FLT_MIN, FLT_MIN);

	FVector vecs[8] = {
		FVector(-0.5f, -0.5f, -0.5f),
		FVector(0.5f, -0.5f, -0.5f),
		FVector(-0.5f, 0.5f, -0.5f),
		FVector(0.5f, 0.5f, -0.5f),
		FVector(-0.5f, -0.5f, 0.5f),
		FVector(0.5f, -0.5f, 0.5f),
		FVector(-0.5f, 0.5f, 0.5f),
		FVector(0.5f, 0.5f, 0.5f),
	};

	FMatrix transform = GetWorldMatrix();
	for ( int i = 0; i < 8; i++ ) {
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

bool UCubeComponent::IsRayIntersect(FRay ray, float hitDistance, FVector& hitPoint) const {
	// OBB (Transformed ray with AABB)
	FMatrix transform = GetWorldMatrix().Inverse();
	FRay transformedRay = FRay(transform.TransformVector(ray.Origin), transform.TransformVector(ray.Direction).GetSafeNormal());

	FAABB AABBorigin = FAABB(FVector(-0.5, -0.5, -0.5), FVector(0.5, 0.5, 0.5));


	auto ws = [](const FVector& v)->FString {
		FString s = L"(";
		s += std::to_wstring(v.X) + L", ";
		s += std::to_wstring(v.Y) + L", ";
		s += std::to_wstring(v.Z) + L")";
		return s;
	};
	FString s = ws(transformedRay.Origin) + L"\t" + ws(transformedRay.Origin + transformedRay.Direction * hitDistance) + L"\n";
	OutputDebugString(s.c_str());

	bool result = Geometry::IsRayIntersectAABB(AABBorigin, transformedRay, hitDistance);
	if (result) {
		hitPoint = GetComponentLocation();
	}
	
	return result;
}
