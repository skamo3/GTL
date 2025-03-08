#include "pch.h"
#include "Vector.h"

const FVector FVector::ZeroVector = FVector(0, 0, 0);
const FVector FVector::OneVector = FVector(1, 1, 1);
const FVector FVector::UpVector = FVector(0, 1, 0);
const FVector FVector::DownVector = FVector(0, -1, 0);
const FVector FVector::ForwardVector = FVector(0, 0, 1);
const FVector FVector::BackwardVector = FVector(0, 0, -1);
const FVector FVector::RightVector = FVector(1, 0, 0);
const FVector FVector::LeftVector = FVector(-1, 0, 0);
const FVector FVector::XAxisVector = FVector(1, 0, 0);
const FVector FVector::YAxisVector = FVector(0, 1, 0);
const FVector FVector::ZAxisVector = FVector(0, 0, 1);

bool FVector::Reciprocal(const FVector& src, FVector& dst)
{
	FVector result;
	if (src.X == 0.f || src.Y == 0.f || src.Z == 0.f)
	{
		return false;
	}

	result.X = 1.f / src.X;
	result.Y = 1.f / src.Y;
	result.Z = 1.f / src.Z;
	
	dst = result;

	return true;
}
