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

	/// <summary>
	/// 주어진 점이 Ray상에서 얼마나 떨어져 있는지 파라미터를 반환
	/// </summary>
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

struct FRayCast
{
public:
	static bool InserSectRaySphere(const FRay& ray, const FVector& sphereCenter, float sphereRadius, OUT float& outT);

	static bool IntersectRayAABB(const FRay& ray, const FVector& boxMin, const FVector& boxMax, OUT float& outT);

	static bool IntersectRayTriangle(const FRay& ray, const FVector& v0, const FVector& v1, const FVector& v2, OUT float& outT);
};