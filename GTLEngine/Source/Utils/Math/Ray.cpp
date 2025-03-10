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
	if (D < SMALL_NUMBER)
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

bool FRayCast::IntersectRayTrianglePlane(const FRay& ray, const FVector& v0, const FVector& v1, const FVector& v2, OUT float& outT)
{
    // 삼각형 평면의 법선 계산
    FVector edge0 = v1 - v0;
    FVector edge1 = v2 - v0;
    FVector normal = edge0.Cross(edge1).GetNormalizedVector();

    // 평면과의 교차 검사
    float t;
    if (!IntersectRayPlane(ray, v0, normal, t))
        return false;

    // Ray 상의 교차점 P 계산
    FVector P = ray.GetOrigin() + ray.GetDirection() * t;

    // 바리센트릭 좌표 계산으로 P가 삼각형 내부에 있는지 판별
    // 바리센트릭 좌표(barycentric coordinates)는 삼각형 내부의 임의의 점을 삼각형의 세 꼭짓점에 대한 가중치의 조합으로 표현하는 좌표계
	// 삼각형의 꼭짓점을 v0, v1, v2 라고 할 때, P = u*v0 + v*v1 + (1-u-v)*v2 로 표현
	// u, v, 1-u-v이 모두 0 이상이고, u+v가 1 이하이면 삼각형 내부에 있다고 판단

    FVector vp0 = P - v0;
    float dot00 = edge0.Dot(edge0);
    float dot01 = edge0.Dot(edge1);
    float dot02 = edge0.Dot(vp0);
    float dot11 = edge1.Dot(edge1);
    float dot12 = edge1.Dot(vp0);

    float invDenom = 1.0f / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    // u와 v가 모두 0 이상이고, u+v가 1 이하이면 삼각형 내부에 있음
    if (u < SMALL_NUMBER || v < SMALL_NUMBER || (u + v) > 1)
        return false;

    outT = t;
    return true;
}

bool FRayCast::IntersectRayPlane(const FRay& ray, const FVector& planePoint, const FVector& planeNormal, OUT float& outT)
{
    // Ray 방향과 평면 법선의 내적 계산
	float denom = ray.GetDirection().Dot(planeNormal);

	// 내적 계산 결과가 0이면 Ray와 평면이 평행
	if (fabs(denom) < SMALL_NUMBER)
	{
		return false;
	}

	// 교차점이 평면 위에 있는지 확인
	float t = (planePoint - ray.GetOrigin()).Dot(planeNormal) / denom;
	if (t < SMALL_NUMBER)
	{
		return false;
	}

	outT = t;
	return true;
}
