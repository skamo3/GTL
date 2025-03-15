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