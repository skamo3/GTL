#include "pch.h"
#include "Math.h"

FMatrix FMath::CreateScaleMatrix(float scale)
{
	return FMatrix::CreateScaleMatrix(scale);
}

FMatrix FMath::CreateScaleMatrix(const FVector& scale)
{
	return FMatrix::CreateScaleMatrix(scale);
}

FMatrix FMath::CreateRotationMatrix(float pitch, float yaw, float roll)
{
	return FMatrix::CreateRotationXYZ(FVector(pitch, yaw, roll));
}

FMatrix FMath::CreateRotationMatrix(const FVector& rotation)
{
	return FMatrix::CreateRotationXYZ(rotation);
}

FMatrix FMath::CreateTranslationMatrix(const FVector& location)
{
	return FMatrix::CreateTranslationMatrix(location);
}

FMatrix FMath::CreateTranslationMatrix(float x, float y, float z)
{
	return FMath::CreateTranslationMatrix(FVector(x, y, z));
}

FMatrix FMath::CreateWorldMatrix(const FVector& position, const FVector& rotation, const FVector& scale)
{
	FMatrix S = CreateScaleMatrix(scale);
	FMatrix R = CreateRotationMatrix(rotation);
	FMatrix T = CreateTranslationMatrix(position);

	// Scale → Rotation → Translation 순서로 행렬을 곱해준다.
	FMatrix worldMatrix = (S * R) * T;
	return worldMatrix;
}

FMatrix FMath::CreateBasisMatrix(const FVector& xAxis, const FVector& yAxis, const FVector& zAxis, const FVector& origin)
{
	return FMatrix::CreateBasisMatrix(xAxis, yAxis, zAxis, origin);
}

//FMatrix FMath::CreateViewMatrixByTargetPos(const FVector& eye, const FVector& target, const FVector& up, bool isLeft)
//{
//	if (isLeft)
//	{
//		return FMatrix::CreateLookAtMatrixLeftHand(eye, target, up);
//	}
//	else
//	{
//		return FMatrix::CreateLookAtMatrixRightHand(eye, target, up);
//	}
//}

FMatrix FMath::CreateViewMatrixByDirection(const FVector& eye, const FVector& direction, const FVector& up, bool isLeft)
{
	if (isLeft)
	{
		return FMatrix::CreateLookToMatrixLeftHand(eye, direction, up);
	}
	else
	{
		return FMatrix::CreateLookToMatrixRightHand(eye, direction, up);
	}
}

FMatrix FMath::CreateOrthographicProjectionMatrix(float screenWidth, float screenHeight, float zNear, float zFar, bool isLeft)
{
	if (isLeft)
	{
		return FMatrix::CreateOrthographicProjectionMatrixLeftHand(screenWidth, screenHeight, zNear, zFar);
	}
	else
	{
		return FMatrix::CreateOrthographicProjectionMatrixRightHand(screenWidth, screenHeight, zNear, zFar);
	}
}

FMatrix FMath::CreatePerspectiveProjectionMatrix(float fov, float width, float height, float zNear, float zFar, bool isLeft)
{
	return CreatePerspectiveProjectionMatrix(fov, width / height, zNear, zFar, isLeft);
}

FMatrix FMath::CreatePerspectiveProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar, bool isLeft)
{
	if (isLeft)
	{
		return FMatrix::CreatePerspectiveProjectionMatrixLeftHand(fov, aspectRatio, zNear, zFar);
	}
	else
	{
		return FMatrix::CreatePerspectiveProjectionMatrixRightHand(fov, aspectRatio, zNear, zFar);
	}
}


FMatrix FMath::CreateMVP(const FMatrix& modelMat, const FMatrix& viewMat, const FMatrix& projMat)
{
	// 보통 DirectX는 M*V*P 순으로 곱해준다.
	// OpenGL도 기본 개념은 동일하나, 행렬이 row-major vs column-major 차이 정도만 있음.
	return modelMat * viewMat * projMat;
}

FVector FMath::TransformNormal(const FVector& v, const FMatrix& m)
{
	FVector result;

	// (x, y, z, 0)을 m과 곱한다 (Translation은 무시)
	// row-vector × matrix 형태로 계산
	// v' = [v.x, v.y, v.z, 0] × m
	result.X = v.X * m.M[0][0] + v.Y * m.M[1][0] + v.Z * m.M[2][0];
	result.Y = v.X * m.M[0][1] + v.Y * m.M[1][1] + v.Z * m.M[2][1];
	result.Z = v.X * m.M[0][2] + v.Y * m.M[1][2] + v.Z * m.M[2][2];

	return result;
}
