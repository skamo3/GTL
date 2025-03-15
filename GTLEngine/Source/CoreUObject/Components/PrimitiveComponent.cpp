#include "pch.h"
#include "PrimitiveComponent.h"

UPrimitiveComponent::UPrimitiveComponent()
	: USceneComponent(), PrimitiveType(EPrimitiveType::None)
{
}

void UPrimitiveComponent::Tick(float TickTime)
{
}

void UPrimitiveComponent::Destroy()
{
}

FMatrix UPrimitiveComponent::GetWorldMatrix() const {
    FMatrix ScaleMat = FMatrix::GetScaleMatrix(GetComponentScale());
    FMatrix RotMat = FMatrix::GetRotateMatrix(GetComponentRotation());
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
	return ScaleMat * RotTrs;;
}

bool UPrimitiveComponent::IsRayIntersectWithTriangle(const FRay& ray, const FVector& v0, const FVector& v1, const FVector& v2, float hitDistance, FVector& hitpoint) const {

    hitpoint = FVector::Zero();

    const float epsilon = 1e-6f;
    FVector edge1 = v1 - v0;
    FVector edge2 = v2 - v0;
    FVector ray_cross_e2 = ray.GetNormalizedDirection().Cross(edge2);
    
    float det = edge1.Dot(ray_cross_e2);

    if ( det > -epsilon && det < epsilon )
        return false;    // This ray is parallel to this triangle.

    float inv_det = 1.0 / det;
    FVector s = ray.Origin - v0;
    float u = inv_det * s.Dot(ray_cross_e2);

    if ( (u < 0 && abs(u) > epsilon) || (u > 1 && abs(u - 1) > epsilon) )
        return false;

    FVector s_cross_e1 = s.Cross(edge1);
    float v = inv_det * ray.GetNormalizedDirection().Dot(s_cross_e1);

    if ( (v < 0 && abs(v) > epsilon) || (u + v > 1 && abs(u + v - 1) > epsilon) )
        return false;

    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = inv_det * edge2.Dot(s_cross_e1);

    if ( t > epsilon ) // ray intersection
    {
        hitpoint = ray.Origin + ray.GetNormalizedDirection() * t;
        return true;
    } else { // This means that there is a line intersection but not a ray intersection.
        return false;
    }
}