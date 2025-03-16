#pragma once
#include "Core/Resource/Types.h"

class Geometry {
public:
	static bool IsRayIntersectAABB(FAABB aabb, FRay ray, float maxDistance);
	static bool IsRayIntersectWithTriangle(const FRay& ray, const FVector& v0, const FVector& v1, const FVector& v2, float hitDistance, FVector& hitpoint);
	static FRay CreateRayWithMouse(float NDCMouseX, float NDCMouseY);
};

