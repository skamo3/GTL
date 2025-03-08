#pragma once
#include "Vector.h"

struct FRay
{

public:
	FRay() : Origin(FVector::ZeroVector), Direction(FVector::UpVector) {}
	FRay(const FVector& origin, const FVector& direction);

	inline FVector GetOrigin() const { return Origin; }
	inline FVector GetDirection() const { return Direction; }

	inline void SetOrigin(const FVector& origin) { Origin = origin; }
	inline void SetDirection(const FVector& direction) { Direction = direction; }

	inline FVector GetPoint(float t) const { return Origin + Direction * t; }

	inline bool operator==(const FRay& other) const
	{
		return Origin == other.Origin && Direction == other.Direction;
	}
	inline bool operator!=(const FRay& other) const
	{
		return !(*this == other);
	}

	inline float GetParameter(const FVector& point) const
	{
		return (point - Origin).Dot(Direction);
	}

	inline float DisSq(const FVector& point) const
	{
		float rayParam = GetParameter(point);
		if (rayParam < 0)
		{
			return (point - Origin).SquaredLength();
		}
		else
		{
			FVector pointOnRay = Origin + Direction * rayParam;
			return (point - pointOnRay).SquaredLength();
		}
	}

	inline float Distance(const FVector& point) const
	{
		return sqrtf(DisSq(point));
	}

	FVector ClosestPoint(const FVector& point) const
	{
		float rayParam = GetParameter(point);
		if (rayParam < 0)
		{
			return Origin;
		}
		else
		{
			return Origin + Direction * rayParam;
		}
	}

private:
	FVector Origin;
	FVector Direction;
};

