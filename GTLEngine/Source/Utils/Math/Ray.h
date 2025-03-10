#pragma once
#include "Vector.h"

struct FRay
{

private:
	/// <summary>
	/// Ray의 시작점
	/// </summary>
	FVector Origin;

	/// <summary>
	/// Ray의 방향
	/// </summary>
	FVector Direction;

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
};

struct FRayCast
{
public:
	/// <summary>
	/// Ray와 구(Sphere)와의 교차를 검사
	/// </summary>
	/// <param name="ray">교차 검사를 수행할 Ray</param>
	/// <param name="sphereCenter">구의 중심</param>
	/// <param name="sphereRadius">구의 반지름</param>
	/// <param name="outT">교차 시 Ray 상의 t 값</param>
	/// <returns>교차가 있으면 true, 없으면 false</returns>
	static bool InserSectRaySphere(const FRay& ray, const FVector& sphereCenter, float sphereRadius, OUT float& outT);

	/// <summary>
	/// Ray와 축에 정렬된 경계 상자(AABB)와의 교차를 슬랩(Slab) 기법을 이용해 검사
	/// </summary>
	/// <param name="ray">교차 검사를 수행할 Ray</param>
	/// <param name="boxMin">AABB의 최소 점 (x, y, z 최소값)</param>
	/// <param name="boxMax">AABB의 최대 점 (x, y, z 최대값)</param>
	/// <param name="outT">Ray와 상자와의 첫 번째 교차 시 Ray 상의 t 값</param>
	/// <returns>교차가 있으면 true, 없으면 false</returns>
	static bool IntersectRayAABB(const FRay& ray, const FVector& boxMin, const FVector& boxMax, OUT float& outT);

	/// <summary>
	/// <para>Ray와 삼각형 평면(삼각형을 이루는 v0, v1, v2가 있는 평면)과의 교차를 검사</para>
	/// 먼저, 삼각형의 평면에 대한 교차를 평면 방정식을 이용해 계산 후, 그 교차점이 삼각형 내부에 있는지를 바리센트릭 좌표(barycentric coordinates)를 이용해 판단
	/// </summary>
	/// <param name="ray">교차 검사를 수행할 Ray</param>
	/// <param name="v0">삼각형의 첫 번째 꼭짓점</param>
	/// <param name="v1">삼각형의 두 번째 꼭짓점</param>
	/// <param name="v2">삼각형의 세 번째 꼭짓점</param>
	/// <param name="outT">교차 시 Ray 상의 t 값</param>
	/// <returns>교차가 있고 삼각형 내부에 있으면 true, 아니면 false</returns>
	static bool IntersectRayTrianglePlane(const FRay& ray, const FVector& v0, const FVector& v1, const FVector& v2, OUT float& outT);

	/// <summary>
	/// <para>주어진 Ray와 평면(planePoint와 planeNormal으로 정의)과의 단순 교차를 검사</para>
	/// 평면 방정식을 이용해 교차 파라미터 t를 이용해 교차 검사
	/// </summary>
	/// <param name="ray">교차 검사를 수행할 Ray</param>
	/// <param name="planePoint">평면 위의 한 점</param>
	/// <param name="planeNormal">평면의 법선 벡터</param>
	/// <param name="outT">교차 시 Ray 상의 t 값</param>
	/// <returns>교차가 있으면 true, 없으면 false</returns>
	static bool IntersectRayPlane(const FRay& ray, const FVector& planePoint, const FVector& planeNormal, OUT float& outT);
};