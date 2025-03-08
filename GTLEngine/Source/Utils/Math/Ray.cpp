#include "pch.h"
#include "Ray.h"

FRay::FRay(const FVector& origin, const FVector& direction)
{
	Origin = origin;
	Direction = direction.GetNormalizedVector();
}