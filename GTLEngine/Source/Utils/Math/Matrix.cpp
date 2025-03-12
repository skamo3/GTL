#include "pch.h"
#include "Matrix.h"


const FMatrix FMatrix::Identity = FMatrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

FMatrix::FMatrix()
{
	M[0][0] = 1; M[0][1] = 0;  M[0][2] = 0;  M[0][3] = 0;
	M[1][0] = 0; M[1][1] = 1;  M[1][2] = 0;  M[1][3] = 0;
	M[2][0] = 0; M[2][1] = 0;  M[2][2] = 1;  M[2][3] = 0;
	M[3][0] = 0; M[3][1] = 0;  M[3][2] = 0;  M[3][3] = 1;
}

FMatrix::FMatrix(const FMatrix& other)
{
	M[0][0] = other.M[0][0]; M[0][1] = other.M[0][1];  M[0][2] = other.M[0][2];  M[0][3] = other.M[0][3];
	M[1][0] = other.M[1][0]; M[1][1] = other.M[1][1];  M[1][2] = other.M[1][2];  M[1][3] = other.M[1][3];
	M[2][0] = other.M[2][0]; M[2][1] = other.M[2][1];  M[2][2] = other.M[2][2];  M[2][3] = other.M[2][3];
	M[3][0] = other.M[3][0]; M[3][1] = other.M[3][1];  M[3][2] = other.M[3][2];  M[3][3] = other.M[3][3];
}

FMatrix::FMatrix(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
{
	M[0][0] = m00; M[0][1] = m01;  M[0][2] = m02;  M[0][3] = m03;
	M[1][0] = m10; M[1][1] = m11;  M[1][2] = m12;  M[1][3] = m13;
	M[2][0] = m20; M[2][1] = m21;  M[2][2] = m22;  M[2][3] = m23;
	M[3][0] = m30; M[3][1] = m31;  M[3][2] = m32;  M[3][3] = m33;
}

FVector FMatrix::ProjectVector(const FVector& v, float inW, float& outW) const
{
	float x = M[0][0] * v.X + M[0][1] * v.Y + M[0][2] * v.Z + M[0][3] * inW;
	float y = M[1][0] * v.X + M[1][1] * v.Y + M[1][2] * v.Z + M[1][3] * inW;
	float z = M[2][0] * v.X + M[2][1] * v.Y + M[2][2] * v.Z + M[2][3] * inW;
	float wOut = M[3][0] * v.X + M[3][1] * v.Y + M[3][2] * v.Z + M[3][3] * inW;

	return FVector(x, y, z);
}

FVector FMatrix::AffineTransform(const FVector& v) const
{
	float x = M[0][0] * v.X + M[0][1] * v.Y + M[0][2] * v.Z;
	float y = M[1][0] * v.X + M[1][1] * v.Y + M[1][2] * v.Z;
	float z = M[2][0] * v.X + M[2][1] * v.Y + M[2][2] * v.Z;

	return FVector(x, y, z);
}

bool FMatrix::Inverse(const FMatrix& src, FMatrix& dst)
{
	const FMatrix& cpyMat = src;
	FMatrix result;

	float det[4];
	FMatrix temp;

	temp.M[0][0] = cpyMat.M[2][2] * cpyMat.M[3][3] - cpyMat.M[2][3] * cpyMat.M[3][2];
	temp.M[0][1] = cpyMat.M[1][2] * cpyMat.M[3][3] - cpyMat.M[1][3] * cpyMat.M[3][2];
	temp.M[0][2] = cpyMat.M[1][2] * cpyMat.M[2][3] - cpyMat.M[1][3] * cpyMat.M[2][2];

	temp.M[1][0] = cpyMat.M[2][2] * cpyMat.M[3][3] - cpyMat.M[2][3] * cpyMat.M[3][2];
	temp.M[1][1] = cpyMat.M[0][2] * cpyMat.M[3][3] - cpyMat.M[0][3] * cpyMat.M[3][2];
	temp.M[1][2] = cpyMat.M[0][2] * cpyMat.M[2][3] - cpyMat.M[0][3] * cpyMat.M[2][2];

	temp.M[2][0] = cpyMat.M[1][2] * cpyMat.M[3][3] - cpyMat.M[1][3] * cpyMat.M[3][2];
	temp.M[2][1] = cpyMat.M[0][2] * cpyMat.M[3][3] - cpyMat.M[0][3] * cpyMat.M[3][2];
	temp.M[2][2] = cpyMat.M[0][2] * cpyMat.M[1][3] - cpyMat.M[0][3] * cpyMat.M[1][2];

	temp.M[3][0] = cpyMat.M[1][2] * cpyMat.M[2][3] - cpyMat.M[1][3] * cpyMat.M[2][2];
	temp.M[3][1] = cpyMat.M[0][2] * cpyMat.M[2][3] - cpyMat.M[0][3] * cpyMat.M[2][2];
	temp.M[3][2] = cpyMat.M[0][2] * cpyMat.M[1][3] - cpyMat.M[0][3] * cpyMat.M[1][2];

	det[0] = cpyMat.M[1][1] * temp.M[0][0] - cpyMat.M[2][1] * temp.M[0][1] + cpyMat.M[3][1] * temp.M[0][2];
	det[1] = cpyMat.M[0][1] * temp.M[1][0] - cpyMat.M[2][1] * temp.M[1][1] + cpyMat.M[3][1] * temp.M[1][2];
	det[2] = cpyMat.M[0][1] * temp.M[2][0] - cpyMat.M[1][1] * temp.M[2][1] + cpyMat.M[3][1] * temp.M[2][2];
	det[3] = cpyMat.M[0][1] * temp.M[3][0] - cpyMat.M[1][1] * temp.M[3][1] + cpyMat.M[2][1] * temp.M[3][2];

	const float determinant = cpyMat.M[0][0] * det[0] - cpyMat.M[1][0] * det[1] + cpyMat.M[2][0] * det[2] - cpyMat.M[3][0] * det[3];

	if (determinant < SMALL_NUMBER)
	{
		dst = FMatrix::Identity;
		return false;
	}

	const float Rdet = 1.0 / determinant;

	result.M[0][0] = det[0] * Rdet;
	result.M[0][1] = -det[1] * Rdet;
	result.M[0][2] = det[2] * Rdet;
	result.M[0][3] = -det[3] * Rdet;
	result.M[1][0] = -cpyMat.M[1][0] * temp.M[0][0] + cpyMat.M[2][0] * temp.M[0][1] - cpyMat.M[3][0] * temp.M[0][2] * Rdet;

	result.M[1][1] = Rdet * (cpyMat.M[0][0] * temp.M[1][0] - cpyMat.M[2][0] * temp.M[1][1] + cpyMat.M[3][0] * temp.M[1][2]);
	result.M[1][2] = -Rdet * (cpyMat.M[0][0] * temp.M[2][0] - cpyMat.M[1][0] * temp.M[2][1] + cpyMat.M[3][0] * temp.M[2][2]);
	result.M[1][3] = Rdet * (cpyMat.M[0][0] * temp.M[3][0] - cpyMat.M[1][0] * temp.M[3][1] + cpyMat.M[2][0] * temp.M[3][2]);
	result.M[2][0] = Rdet * (
		cpyMat.M[1][0] * (cpyMat.M[2][1] * cpyMat.M[3][3] - cpyMat.M[2][3] * cpyMat.M[3][1]) -
		cpyMat.M[2][0] * (cpyMat.M[1][1] * cpyMat.M[3][3] - cpyMat.M[1][3] * cpyMat.M[3][1]) +
		cpyMat.M[3][0] * (cpyMat.M[1][1] * cpyMat.M[2][3] - cpyMat.M[1][3] * cpyMat.M[2][1])
		);
	result.M[2][1] = -Rdet * (
		cpyMat.M[0][0] * (cpyMat.M[2][1] * cpyMat.M[3][3] - cpyMat.M[2][3] * cpyMat.M[3][1]) -
		cpyMat.M[2][0] * (cpyMat.M[0][1] * cpyMat.M[3][3] - cpyMat.M[0][3] * cpyMat.M[3][1]) +
		cpyMat.M[3][0] * (cpyMat.M[0][1] * cpyMat.M[2][3] - cpyMat.M[0][3] * cpyMat.M[2][1])
		);
	result.M[2][2] = Rdet * (
		cpyMat.M[0][0] * (cpyMat.M[1][1] * cpyMat.M[3][3] - cpyMat.M[1][3] * cpyMat.M[3][1]) -
		cpyMat.M[1][0] * (cpyMat.M[0][1] * cpyMat.M[3][3] - cpyMat.M[0][3] * cpyMat.M[3][1]) +
		cpyMat.M[3][0] * (cpyMat.M[0][1] * cpyMat.M[1][3] - cpyMat.M[0][3] * cpyMat.M[1][1])
		);
	result.M[2][3] = -Rdet * (
		cpyMat.M[0][0] * (cpyMat.M[1][1] * cpyMat.M[2][3] - cpyMat.M[1][3] * cpyMat.M[2][1]) -
		cpyMat.M[1][0] * (cpyMat.M[0][1] * cpyMat.M[2][3] - cpyMat.M[0][3] * cpyMat.M[2][1]) +
		cpyMat.M[2][0] * (cpyMat.M[0][1] * cpyMat.M[1][3] - cpyMat.M[0][3] * cpyMat.M[1][1])
		);
	result.M[3][0] = -Rdet * (
		cpyMat.M[1][0] * (cpyMat.M[2][1] * cpyMat.M[3][2] - cpyMat.M[2][2] * cpyMat.M[3][1]) -
		cpyMat.M[2][0] * (cpyMat.M[1][1] * cpyMat.M[3][2] - cpyMat.M[1][2] * cpyMat.M[3][1]) +
		cpyMat.M[3][0] * (cpyMat.M[1][1] * cpyMat.M[2][2] - cpyMat.M[1][2] * cpyMat.M[2][1])
		);
	result.M[3][1] = Rdet * (
		cpyMat.M[0][0] * (cpyMat.M[2][1] * cpyMat.M[3][2] - cpyMat.M[2][2] * cpyMat.M[3][1]) -
		cpyMat.M[2][0] * (cpyMat.M[0][1] * cpyMat.M[3][2] - cpyMat.M[0][2] * cpyMat.M[3][1]) +
		cpyMat.M[3][0] * (cpyMat.M[0][1] * cpyMat.M[2][2] - cpyMat.M[0][2] * cpyMat.M[2][1])
		);
	result.M[3][2] = -Rdet * (
		cpyMat.M[0][0] * (cpyMat.M[1][1] * cpyMat.M[3][2] - cpyMat.M[1][2] * cpyMat.M[3][1]) -
		cpyMat.M[1][0] * (cpyMat.M[0][1] * cpyMat.M[3][2] - cpyMat.M[0][2] * cpyMat.M[3][1]) +
		cpyMat.M[3][0] * (cpyMat.M[0][1] * cpyMat.M[1][2] - cpyMat.M[0][2] * cpyMat.M[1][1])
		);
	result.M[3][3] = Rdet * (
		cpyMat.M[0][0] * (cpyMat.M[1][1] * cpyMat.M[2][2] - cpyMat.M[1][2] * cpyMat.M[2][1]) -
		cpyMat.M[1][0] * (cpyMat.M[0][1] * cpyMat.M[2][2] - cpyMat.M[0][2] * cpyMat.M[2][1]) +
		cpyMat.M[2][0] * (cpyMat.M[0][1] * cpyMat.M[1][2] - cpyMat.M[0][2] * cpyMat.M[1][1])
		);

	dst = result;
	return true;
}

FVector FMatrix::GetScaleVector() const
{
	FVector scale3D(1, 1, 1);

	for (int i = 0; i < 3; i++)
	{
		float squareSum = (M[i][0] * M[i][0]) + (M[i][1] * M[i][1]) + (M[i][2] * M[i][2]);
		if (squareSum == 0.f)
		{
			scale3D[i] = 0.f;
		}
		else
		{
			scale3D[i] = sqrtf(squareSum);
		}
	}

	return scale3D;
}

FMatrix FMatrix::GetMatrixWithOutScale() const
{
	FMatrix result = *this;
	result.RemoveScaling();

	return result;
}

FMatrix FMatrix::AppendTranslation(const FVector& translation) const
{
	FMatrix Result;

	float* dest = &Result.M[0][0];
	const float* src = &M[0][0];
	const float* trans = &translation.X;

	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
	dest[3] = src[3];
	dest[4] = src[4];
	dest[5] = src[5];
	dest[6] = src[6];
	dest[7] = src[7];
	dest[8] = src[8];
	dest[9] = src[9];
	dest[10] = src[10];
	dest[11] = src[11];
	dest[12] = src[12] + trans[0];
	dest[13] = src[13] + trans[1];
	dest[14] = src[14] + trans[2];
	dest[15] = src[15];

	return Result;
}

FMatrix FMatrix::CreateRotationX(float angle)
{
	float radian = angle * (PI / 180.0f);
	float sinAngle = sin(radian);
	float cosAngle = cos(radian);

	FMatrix rotationX(
		1.f, 0.f, 0.f, 0.f,
		0.f, cosAngle, -sinAngle, 0.f,
		0.f, sinAngle, cosAngle, 0.f,
		0.f, 0.f, 0.f, 1.f
	);

	return rotationX;
}

FMatrix FMatrix::CreateRotationY(float angle)
{
	float radian = angle * (PI / 180.0f);
	float sinAngle = sin(radian);
	float cosAngle = cos(radian);

	FMatrix rotationY(
		cosAngle, 0.f, sinAngle, 0.f,
		0.f, 1.f, 0.f, 0.f,
		-sinAngle, 0.f, cosAngle, 0.f,
		0.f, 0.f, 0.f, 1.f
	);

	return rotationY;
}

FMatrix FMatrix::CreateRotationZ(float angle)
{
	float radian = angle * (PI / 180.0f);
	float sinAngle = sin(radian);
	float cosAngle = cos(radian);

	FMatrix rotationZ(
		cosAngle, -sinAngle, 0.f, 0.f,
		sinAngle, cosAngle, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	);

	return rotationZ;
}

FMatrix FMatrix::CreateRotationXYZ(const FVector& rotation)
{
	FMatrix rotationMatrix = CreateRotationX(rotation.X) * CreateRotationY(rotation.Y) * CreateRotationZ(rotation.Z);
	return rotationMatrix;
}

FMatrix FMatrix::CreateRotationQuat(const FQuaternion& q)
{
	FQuaternion normalizedQuat = q.GetNormalizeQuaternion();

	float xx = normalizedQuat.X * normalizedQuat.X;
	float yy = normalizedQuat.Y * normalizedQuat.Y;
	float zz = normalizedQuat.Z * normalizedQuat.Z;
	float xy = normalizedQuat.X * normalizedQuat.Y;
	float xz = normalizedQuat.X * normalizedQuat.Z;
	float yz = normalizedQuat.Y * normalizedQuat.Z;
	float wx = normalizedQuat.W * normalizedQuat.X;
	float wy = normalizedQuat.W * normalizedQuat.Y;
	float wz = normalizedQuat.W * normalizedQuat.Z;

	return FMatrix(
		1 - 2 * (yy + zz), 2 * (xy - wz), 2 * (xz + wy), 0,
		2 * (xy + wz), 1 - 2 * (xx + zz), 2 * (yz - wx), 0,
		2 * (xz - wy), 2 * (yz + wx), 1 - 2 * (xx + yy), 0,
		0, 0, 0, 1
	);
}

FMatrix FMatrix::CreateScaleMatrix(float scale)
{
	FMatrix S(
		scale, 0.f, 0.f, 0.f,
		0.f, scale, 0.f, 0.f,
		0.f, 0.f, scale, 0.f,
		0.f, 0.f, 0.f, 1.f
	);
	return S;
}

FMatrix FMatrix::CreateScaleMatrix(const FVector& scale)
{
	FMatrix S(
		scale.X, 0.f, 0.f, 0.f,
		0.f, scale.Y, 0.f, 0.f,
		0.f, 0.f, scale.Z, 0.f,
		0.f, 0.f, 0.f, 1.f
	);
	return S;
}

FMatrix FMatrix::CreateBasisMatrix(const FVector& xAxis, const FVector& yAxis, const FVector& zAxis, const FVector& origin)
{
	FMatrix basisMatrix;
	basisMatrix.M[0][0] = xAxis.X; 	basisMatrix.M[0][1] = yAxis.X; 	basisMatrix.M[0][2] = zAxis.X; 	basisMatrix.M[0][3] = 0.0f;

	basisMatrix.M[1][0] = xAxis.Y;	basisMatrix.M[1][1] = yAxis.Y;	basisMatrix.M[1][2] = zAxis.Y;basisMatrix.M[1][3] = 0.0f;

	basisMatrix.M[2][0] = xAxis.Z;	basisMatrix.M[2][1] = yAxis.Z;	basisMatrix.M[2][2] = zAxis.Z;	basisMatrix.M[2][3] = 0.0f;

	basisMatrix.M[3][0] = origin.Dot(xAxis);	basisMatrix.M[3][1] = origin.Dot(yAxis);	basisMatrix.M[3][2] = origin.Dot(zAxis);	basisMatrix.M[3][3] = 1.0f;

	return basisMatrix;
}

FMatrix FMatrix::CreateTranslationMatrix(const FVector& location)
{
	FMatrix T(
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		location.X, location.Y, location.Z, 1.f
	);
	return T;
}

FMatrix FMatrix::CreateLookToMatrixLeftHand(const FVector& eye, const FVector& toDir, const FVector& up)
{
	FVector zAxis = toDir.GetNormalizedVector();

	FVector xAxis = FVector::Cross(up, zAxis).GetNormalizedVector();

	FVector yAxis = FVector::Cross(zAxis, xAxis);

	FMatrix viewMatrix;

	viewMatrix.M[0][0] = xAxis.X;  viewMatrix.M[0][1] = yAxis.X;  viewMatrix.M[0][2] = zAxis.X;  viewMatrix.M[0][3] = 0.0f;
	viewMatrix.M[1][0] = xAxis.Y;  viewMatrix.M[1][1] = yAxis.Y;  viewMatrix.M[1][2] = zAxis.Y;  viewMatrix.M[1][3] = 0.0f;
	viewMatrix.M[2][0] = xAxis.Z;  viewMatrix.M[2][1] = yAxis.Z;  viewMatrix.M[2][2] = zAxis.Z;  viewMatrix.M[2][3] = 0.0f;

	viewMatrix.M[3][0] = -eye.Dot(xAxis);
	viewMatrix.M[3][1] = -eye.Dot(yAxis);
	viewMatrix.M[3][2] = -eye.Dot(zAxis);
	viewMatrix.M[3][3] = 1.0f;

	return viewMatrix;
}

FMatrix FMatrix::CreateLookToMatrixRightHand(const FVector& eye, const FVector& toDir, const FVector& up)
{
	FVector zAxis = (-toDir).GetNormalizedVector();

	FVector xAxis = up.Cross(zAxis).GetNormalizedVector();

	FVector yAxis = zAxis.Cross(xAxis);

	FMatrix viewMatrix;
	viewMatrix.M[0][0] = xAxis.X;   viewMatrix.M[0][1] = yAxis.X;   viewMatrix.M[0][2] = zAxis.X;   viewMatrix.M[0][3] = 0.0f;
	viewMatrix.M[1][0] = xAxis.Y;   viewMatrix.M[1][1] = yAxis.Y;   viewMatrix.M[1][2] = zAxis.Y;   viewMatrix.M[1][3] = 0.0f;
	viewMatrix.M[2][0] = xAxis.Z;   viewMatrix.M[2][1] = yAxis.Z;   viewMatrix.M[2][2] = zAxis.Z;   viewMatrix.M[2][3] = 0.0f;

	viewMatrix.M[3][0] = -eye.Dot(xAxis);
	viewMatrix.M[3][1] = -eye.Dot(yAxis);
	viewMatrix.M[3][2] = -eye.Dot(zAxis);
	viewMatrix.M[3][3] = 1.0f;

	return viewMatrix;
}

FMatrix FMatrix::CreateOrthographicProjectionMatrixLeftHand(float screenWidth, float screenHeight, float zNear, float zFar)
{
	float fRange = 1.0f / (zFar - zNear);

	FMatrix proj;
	proj.M[0][0] = 2.0f / screenWidth; proj.M[0][1] = 0.0f; proj.M[0][2] = 0.0f; proj.M[0][3] = 0.0f;
	proj.M[1][0] = 0.0f; proj.M[1][1] = 2.0f / screenHeight; proj.M[1][2] = 0.0f; proj.M[1][3] = 0.0f;
	proj.M[2][0] = 0.0f; proj.M[2][1] = 0.0f; proj.M[2][2] = fRange; proj.M[2][3] = 0.0f;
	proj.M[3][0] = 0.0f; proj.M[3][1] = 0.0f; proj.M[3][2] = -zNear * fRange; proj.M[3][3] = 1.0f;

	return proj;
}

FMatrix FMatrix::CreateOrthographicProjectionMatrixRightHand(float screenWidth, float screenHeight, float zNear, float zFar)
{
	float fRange = 1.0f / (zFar - zNear);

	FMatrix proj;
	proj.M[0][0] = 2.0f / screenWidth; proj.M[0][1] = 0.0f; proj.M[0][2] = 0.0f; proj.M[0][3] = 0.0f;
	proj.M[1][0] = 0.0f; proj.M[1][1] = 2.0f / screenHeight; proj.M[1][2] = 0.0f; proj.M[1][3] = 0.0f;
	proj.M[2][0] = 0.0f; proj.M[2][1] = 0.0f; proj.M[2][2] = fRange; proj.M[2][3] = 0.0f;
	proj.M[3][0] = 0.0f; proj.M[3][1] = 0.0f; proj.M[3][2] = zNear * fRange; proj.M[3][3] = 1.0f;

	return proj;
}

FMatrix FMatrix::CreatePerspectiveProjectionMatrixLeftHand(float fov, float aspectRatio, float zNear, float zFar)
{
	float rad = fov * (PI / 180.f);
	float tanHalfFov = std::tan(rad * 0.5f);

	// yScale = 1 / tan(fov/2), xScale = yScale / aspectRatio
	float height = 1 / tanHalfFov;
	float width = height / aspectRatio;

	float fRange = zFar / (zFar - zNear);

	FMatrix proj;

	proj.M[0][0] = width; proj.M[0][1] = 0.0f; proj.M[0][2] = 0.0f;  proj.M[0][3] = 0.0f;
	proj.M[1][0] = 0.0f; proj.M[1][1] = height; proj.M[1][2] = 0.0f;  proj.M[1][3] = 0.0f;
	proj.M[2][0] = 0.0f; proj.M[2][1] = 0.0f; proj.M[2][2] = fRange; proj.M[2][3] = 1.0f;
	proj.M[3][0] = 0.0f; proj.M[3][1] = 0.0f; proj.M[3][2] = -zNear * fRange; proj.M[3][3] = 0.0f;

	return proj;
}

FMatrix FMatrix::CreatePerspectiveProjectionMatrixRightHand(float fov, float aspectRatio, float zNear, float zFar)
{
	float rad = fov * (PI / 180.f);
	float tanHalfFov = std::tan(rad * 0.5f);

	float height = 1.0f / tanHalfFov;
	float width = height / aspectRatio;

	float zRange = zFar - zNear;

	FMatrix proj;

	proj.M[0][0] = width; proj.M[0][1] = 0.0f; proj.M[0][2] = 0.0f; proj.M[0][3] = 0.0f;
	proj.M[1][0] = 0.0f; proj.M[1][1] = height; proj.M[1][2] = 0.0f; proj.M[1][3] = 0.0f;
	proj.M[2][0] = 0.0f; proj.M[2][1] = 0.0f; proj.M[2][2] = -(zFar + zNear) / zRange; proj.M[2][3] = -1.0f;
	proj.M[3][0] = 0.0f; proj.M[3][1] = 0.0f; proj.M[3][2] = -(2.0f * zFar * zNear) / zRange; proj.M[3][3] = 0.0f;

	return proj;
}