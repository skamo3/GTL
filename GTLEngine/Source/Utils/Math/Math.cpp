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

FVector FMath::TransformPosition(const FVector& pos, const FMatrix& m, OUT float& w)
{
	FVector result;
	result.X = m.M[0][0] * pos.X + m.M[1][0] * pos.Y + m.M[2][0] * pos.Z + m.M[3][0];
	result.Y = m.M[0][1] * pos.X + m.M[1][1] * pos.Y + m.M[2][1] * pos.Z + m.M[3][1];
	result.Z = m.M[0][2] * pos.X + m.M[1][2] * pos.Y + m.M[2][2] * pos.Z + m.M[3][2];
	w = m.M[0][3] * pos.X + m.M[1][3] * pos.Y + m.M[2][3] * pos.Z + m.M[3][3];

	return result;
}

FVector FMath::TransformDirection(const FVector& dir, const FMatrix& m)
{
	FVector result;

	// (x, y, z, 0)을 m과 곱한다 (Translation은 무시)
	// row-vector × matrix 형태로 계산
	// v' = [dir.x, dir.y, dir.z, 0] × m
	result.X = dir.X * m.M[0][0] + dir.Y * m.M[1][0] + dir.Z * m.M[2][0];
	result.Y = dir.X * m.M[0][1] + dir.Y * m.M[1][1] + dir.Z * m.M[2][1];
	result.Z = dir.X * m.M[0][2] + dir.Y * m.M[1][2] + dir.Z * m.M[2][2];

	return result;
}

FRay FMath::CreateRay(const FMatrix& viewMatrix, const FMatrix& projMatrix, const FVector& mousePos, float screenWidth, float screenHeight)
{
	// Screen 좌표계를 NDC 좌표계로 변환
	float ndcX = (2.0f * mousePos.X) / screenWidth - 1.0f;
	float ndcY = 1.0f - (2.0f * mousePos.Y) / screenHeight;

	return CreateRay(viewMatrix, projMatrix, ndcX, ndcY, screenWidth, screenHeight);
}

FRay FMath::CreateRay(const FMatrix& viewMatrix, const FMatrix& projMatrix, float ndcMouseX, float ndcMouseY, float screenWidth, float screenHeight)
{
	FRay resultRay;

	FVector startClip = FVector(ndcMouseX, ndcMouseY, 0.0f);
	FVector endClip = FVector(ndcMouseX, ndcMouseY, 1.0f);

	// View-Projection 행렬의 역행렬 계산
	FMatrix viewProj = viewMatrix * projMatrix;
	FMatrix invViewProj;
	if (FMatrix::Inverse(viewProj, invViewProj) == false)
	{
		return resultRay;
	}

	// NDC 좌표계를 월드 좌표계로 변환
	float startW = 0;
	FVector startWorldPos = TransformPosition(startClip, invViewProj, startW);
	startWorldPos /= startW;

	float endW = 0;
	FVector endWorldPos = TransformPosition(endClip, invViewProj, endW);
	endWorldPos /= endW;

	// Ray 생성
	resultRay.SetOrigin(startWorldPos);
	resultRay.SetDirection(FVector(endWorldPos - startWorldPos).GetNormalizedVector());

	return resultRay;
}
