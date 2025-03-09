#include "pch.h"
#include "Ray.h"

FRay::FRay(const FVector& origin, const FVector& direction)
{
	Origin = origin;
	Direction = direction.GetNormalizedVector();
}

bool FRayCast::InserSectRaySphere(const FRay& ray, const FVector& sphereCenter, float sphereRadius, OUT float& outT)
{
	// Ray : Origin + tD
	// Sphere : (X - Center) · (X - Center) = r^2

	// 교차점을 구하기 위한 방정식
	// (Origin + tD - Center) · (Origin + tD - Center) = r^2
	// (Origin - Center + tD) · (Origin - Center + tD) = r^2
	// (Origin - Center) · (Origin - Center) + 2t(Origin - Center) · D + t^2(D · D) = r^2
	// t^2 + 2(Origin - Center)·t + (Origin - Center)·(Origin - Center) - r^2 = 0
	
	// 위의 방정식은 a*t^2 + b*t + c = 0 형태로 변환 가능
	// 2차 방정식의 해를 구하기 위해 판별식을 계산
	// D = b^2 - 4ac

	// L = Origin - Center 
	FVector L = ray.GetOrigin() - sphereCenter;

	// b = 2(L · D)
	float b = 2 * ray.GetDirection().Dot(L);

	// c = L · L - r^2
	float c = L.Dot(L) - sphereRadius * sphereRadius;

	float D = b * b - 4 * c;

	// 판별식이 음수인 경우 교차점이 없음
	if (D < 0)
	{
		return false;
	}

	float t0 = (-b - sqrtf(D)) / 2;
	float t1 = (-b + sqrtf(D)) / 2;

	// 두 해 중에서 가장 작은 해를 선택
	if (t0 >= 0)
	{
		outT = t0;
	}
	else if (t1 >= 0)
	{
		outT = t1;
	}
	else
	{
		return false;
	}

	return true;
}

bool FRayCast::IntersectRayAABB(const FRay& ray, const FVector& boxMin, const FVector& boxMax, OUT float& outT)
{
    // 초기 t 범위 설정: tmin은 0 (Ray의 시작점)이고, tmax는 최대값(무한대에 해당)
    float tMin = 0.0f;
    float tMax = FLT_MAX;

    // X축에 대한 슬랩 계산
    {
        float invDx = 1.0f / ray.GetDirection().X;
        float t1 = (boxMin.X - ray.GetOrigin().X) * invDx;
        float t2 = (boxMax.X - ray.GetOrigin().X) * invDx;
        if (t1 > t2)
            std::swap(t1, t2);
        tMin = std::max(tMin, t1);
        tMax = std::min(tMax, t2);
        if (tMin > tMax)
            return false;
    }

    // Y축에 대한 슬랩 계산
    {
        float invDy = 1.0f / ray.GetDirection().Y;
        float t1 = (boxMin.Y - ray.GetOrigin().Y) * invDy;
        float t2 = (boxMax.Y - ray.GetOrigin().Y) * invDy;
        if (t1 > t2)
            std::swap(t1, t2);
        tMin = std::max(tMin, t1);
        tMax = std::min(tMax, t2);
        if (tMin > tMax)
            return false;
    }

    // Z축에 대한 슬랩 계산
    {
        float invDz = 1.0f / ray.GetDirection().Z;
        float t1 = (boxMin.Z - ray.GetOrigin().Z) * invDz;
        float t2 = (boxMax.Z - ray.GetOrigin().Z) * invDz;
        if (t1 > t2)
            std::swap(t1, t2);
        tMin = std::max(tMin, t1);
        tMax = std::min(tMax, t2);
        if (tMin > tMax)
            return false;
    }

    // Ray의 시작점이 내부에 있거나, tMin이 음수인 경우에는 tMax가 사용됩니다.
    if (tMin >= 0)
    {
        outT = tMin;
        return true;
    }
    else if (tMax >= 0)
    {
        outT = tMax;
        return true;
    }
    else
    {
        return false;
    }
}

bool FRayCast::IntersectRayTriangle(const FRay& ray, const FVector& v0, const FVector& v1, const FVector& v2, OUT float& outT)
{
	return false;
}
