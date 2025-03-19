#include "pch.h"
#include "Matrix.h"

#include "Vector.h"

#include "Quat.h"
#include "Transform.h"
#include "Rotator.h"


FMatrix::FMatrix()
{
	// identity matrix
	M[0][0] = 1.0f; M[0][1] = 0.0f; M[0][2] = 0.0f; M[0][3] = 0.0f;
	M[1][0] = 0.0f; M[1][1] = 1.0f; M[1][2] = 0.0f; M[1][3] = 0.0f;
	M[2][0] = 0.0f; M[2][1] = 0.0f; M[2][2] = 1.0f; M[2][3] = 0.0f;
	M[3][0] = 0.0f; M[3][1] = 0.0f; M[3][2] = 0.0f; M[3][3] = 1.0f;
}

FMatrix::FMatrix(const FVector4& InX, const FVector4& InY, const FVector4& InZ, const FVector4& InW)
{
	// row major
	M[0][0] = InX.X; M[0][1] = InX.Y; M[0][2] = InX.Z; M[0][3] = InX.W;
	M[1][0] = InY.X; M[1][1] = InY.Y; M[1][2] = InY.Z; M[1][3] = InY.W;
	M[2][0] = InZ.X; M[2][1] = InZ.Y; M[2][2] = InZ.Z; M[2][3] = InZ.W;
	M[3][0] = InW.X; M[3][1] = InW.Y; M[3][2] = InW.Z; M[3][3] = InW.W;
}

FMatrix::FMatrix(const FRotator& Rotation)
{
	*this = FMatrix::RotateToMatrix(Rotation.Roll, Rotation.Pitch, Rotation.Yaw);
}

FMatrix FMatrix::Identity()
{
	return FMatrix();
}

static constexpr float PIDIV4 = PI / 4.0f;

FMatrix FMatrix::operator+(const FMatrix& Other) const
{
	FMatrix Result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Result.M[i][j] = M[i][j] + Other.M[i][j];
		}
	}
	return Result;
}
FMatrix FMatrix::operator+=(const FMatrix& Other)
{
	*this = *this + Other;
	return *this;
}
FMatrix FMatrix::operator-(const FMatrix& Other) const
{
	FMatrix Result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Result.M[i][j] = M[i][j] - Other.M[i][j];
		}
	}
	return Result;
}
FMatrix FMatrix::operator-=(const FMatrix& Other)
{
	*this = *this - Other;
	return *this;
}
FMatrix FMatrix::operator*(const FMatrix& Other) const
{
	FMatrix Result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Result.M[i][j] = M[i][0] * Other.M[0][j] +
				M[i][1] * Other.M[1][j] +
				M[i][2] * Other.M[2][j] +
				M[i][3] * Other.M[3][j];
		}
	}
	return Result;
}
FMatrix FMatrix::operator*=(const FMatrix& Other)
{
	*this = *this * Other;
	return *this;
}
FMatrix FMatrix::operator*(float Other) const
{
	FMatrix Result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Result.M[i][j] = M[i][j] * Other;
		}
	}
	return Result;
}
FMatrix FMatrix::operator*=(float Other)
{
	*this = *this * Other;
	return *this;
}
bool FMatrix::operator==(const FMatrix& Other) const
{
	bool bEqual = true;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (M[i][j] != Other.M[i][j])
			{
				bEqual = false;
				break;
			}
		}
	}

	return bEqual;
}
bool FMatrix::operator!=(const FMatrix& Other) const
{
	return !(*this == Other);
}

FMatrix FMatrix::GetTransposed() const
{
	FMatrix Result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Result.M[i][j] = M[j][i];
		}
	}
	return Result;
}

float FMatrix::Determinant() const
{
	const float* m = &M[0][0];
	return
		m[0] * (m[5] * (m[10] * m[15] - m[11] * m[14]) - m[6] * (m[9] * m[15] - m[11] * m[13]) + m[7] * (m[9] * m[14] - m[10] * m[13])) -
		m[1] * (m[4] * (m[10] * m[15] - m[11] * m[14]) - m[6] * (m[8] * m[15] - m[11] * m[12]) + m[7] * (m[8] * m[14] - m[10] * m[12])) +
		m[2] * (m[4] * (m[9] * m[15] - m[11] * m[13]) - m[5] * (m[8] * m[15] - m[11] * m[12]) + m[7] * (m[8] * m[13] - m[9] * m[12])) -
		m[3] * (m[4] * (m[9] * m[14] - m[10] * m[13]) - m[5] * (m[8] * m[14] - m[10] * m[12]) + m[6] * (m[8] * m[13] - m[9] * m[12]));
}

FMatrix FMatrix::Inverse() const
{
	const float Det = Determinant();
	if (FMath::Abs(Det) < 1.0e-6f)
	{
		return {};
	}

	FMatrix Result;
	const float* m = &M[0][0];
	const float InvDet = 1.0f / Det;

	Result.M[0][0] = InvDet * (m[5] * (m[10] * m[15] - m[11] * m[14]) - m[6] * (m[9] * m[15] - m[11] * m[13]) + m[7] * (m[9] * m[14] - m[10] * m[13]));
	Result.M[0][1] = -InvDet * (m[1] * (m[10] * m[15] - m[11] * m[14]) - m[2] * (m[9] * m[15] - m[11] * m[13]) + m[3] * (m[9] * m[14] - m[10] * m[13]));
	Result.M[0][2] = InvDet * (m[1] * (m[6] * m[15] - m[7] * m[14]) - m[2] * (m[5] * m[15] - m[7] * m[13]) + m[3] * (m[5] * m[14] - m[6] * m[13]));
	Result.M[0][3] = -InvDet * (m[1] * (m[6] * m[11] - m[7] * m[10]) - m[2] * (m[5] * m[11] - m[7] * m[9]) + m[3] * (m[5] * m[10] - m[6] * m[9]));

	Result.M[1][0] = -InvDet * (m[4] * (m[10] * m[15] - m[11] * m[14]) - m[6] * (m[8] * m[15] - m[11] * m[12]) + m[7] * (m[8] * m[14] - m[10] * m[12]));
	Result.M[1][1] = InvDet * (m[0] * (m[10] * m[15] - m[11] * m[14]) - m[2] * (m[8] * m[15] - m[11] * m[12]) + m[3] * (m[8] * m[14] - m[10] * m[12]));
	Result.M[1][2] = -InvDet * (m[0] * (m[6] * m[15] - m[7] * m[14]) - m[2] * (m[4] * m[15] - m[7] * m[12]) + m[3] * (m[4] * m[14] - m[6] * m[12]));
	Result.M[1][3] = InvDet * (m[0] * (m[6] * m[11] - m[7] * m[10]) - m[2] * (m[4] * m[11] - m[7] * m[8]) + m[3] * (m[4] * m[10] - m[6] * m[8]));

	Result.M[2][0] = InvDet * (m[4] * (m[9] * m[15] - m[11] * m[13]) - m[5] * (m[8] * m[15] - m[11] * m[12]) + m[7] * (m[8] * m[13] - m[9] * m[12]));
	Result.M[2][1] = -InvDet * (m[0] * (m[9] * m[15] - m[11] * m[13]) - m[1] * (m[8] * m[15] - m[11] * m[12]) + m[3] * (m[8] * m[13] - m[9] * m[12]));
	Result.M[2][2] = InvDet * (m[0] * (m[5] * m[15] - m[7] * m[13]) - m[1] * (m[4] * m[15] - m[7] * m[12]) + m[3] * (m[4] * m[13] - m[5] * m[12]));
	Result.M[2][3] = -InvDet * (m[0] * (m[5] * m[11] - m[7] * m[9]) - m[1] * (m[4] * m[11] - m[7] * m[8]) + m[3] * (m[4] * m[9] - m[5] * m[8]));

	Result.M[3][0] = -InvDet * (m[4] * (m[9] * m[14] - m[10] * m[13]) - m[5] * (m[8] * m[14] - m[10] * m[12]) + m[6] * (m[8] * m[13] - m[9] * m[12]));
	Result.M[3][1] = InvDet * (m[0] * (m[9] * m[14] - m[10] * m[13]) - m[1] * (m[8] * m[14] - m[10] * m[12]) + m[2] * (m[8] * m[13] - m[9] * m[12]));
	Result.M[3][2] = -InvDet * (m[0] * (m[5] * m[14] - m[6] * m[13]) - m[1] * (m[4] * m[14] - m[6] * m[12]) + m[2] * (m[4] * m[13] - m[5] * m[12]));
	Result.M[3][3] = InvDet * (m[0] * (m[5] * m[10] - m[6] * m[9]) - m[1] * (m[4] * m[10] - m[6] * m[8]) + m[2] * (m[4] * m[9] - m[5] * m[8]));

	return Result;
}

FMatrix FMatrix::Transpose(const FMatrix& Matrix)
{
	FMatrix Result;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Result.M[i][j] = Matrix.M[j][i];
		}
	}
	return Result;
}

FMatrix FMatrix::GetTranslateMatrix(float X, float Y, float Z)
{
	FMatrix Result;
	Result.M[3][0] = X;
	Result.M[3][1] = Y;
	Result.M[3][2] = Z;
	return Result;
}

FMatrix FMatrix::GetTranslateMatrix(const FVector& Translation)
{
	return GetTranslateMatrix(Translation.X, Translation.Y, Translation.Z);
}

FMatrix FMatrix::GetScaleMatrix(float X, float Y, float Z)
{
	FMatrix Result;
	Result.M[0][0] = X;
	Result.M[1][1] = Y;
	Result.M[2][2] = Z;
	return Result;
}

FMatrix FMatrix::GetScaleMatrix(const FVector& InScale)
{
	return GetScaleMatrix(InScale.X, InScale.Y, InScale.Z);
}

FMatrix FMatrix::GetRotateMatrix(const FRotator& Rot)
{
	return FMatrix(Rot);
}

FMatrix FMatrix::GetRotateMatrix(const FQuat& Q)
{
	// 쿼터니언 요소 추출
	const float x = Q.X, y = Q.Y, z = Q.Z, w = Q.W;

	// 중간 계산값
	const float xx = x * x, yy = y * y, zz = z * z;
	const float xy = x * y, xz = x * z, yz = y * z;
	const float wx = w * x, wy = w * y, wz = w * z;

	// 회전 행렬 구성
	FMatrix Result;

	Result.M[0][0] = 1.0f - 2.0f * (yy + zz);
	Result.M[0][1] = 2.0f * (xy - wz);
	Result.M[0][2] = 2.0f * (xz + wy);
	Result.M[0][3] = 0.0f;

	Result.M[1][0] = 2.0f * (xy + wz);
	Result.M[1][1] = 1.0f - 2.0f * (xx + zz);
	Result.M[1][2] = 2.0f * (yz - wx);
	Result.M[1][3] = 0.0f;

	Result.M[2][0] = 2.0f * (xz - wy);
	Result.M[2][1] = 2.0f * (yz + wx);
	Result.M[2][2] = 1.0f - 2.0f * (xx + yy);
	Result.M[2][3] = 0.0f;

	Result.M[3][0] = 0.0f;
	Result.M[3][1] = 0.0f;
	Result.M[3][2] = 0.0f;
	Result.M[3][3] = 1.0f; // 4x4 행렬이므로 마지막 값은 1

	return Result;
}
/// <summary>
/// 뷰 변환 행렬을 생성합니다.
/// </summary>
/// <param name="EyePosition">카메라의 포지션입니다.</param>
/// <param name="FocusPoint">카메라가 바라보는 곳의 포지션입니다.</param>
/// <param name="UpDirection">카메라의 위쪽 방향입니다.</param>
/// <returns>뷰 변환 행렬을 반환합니다.</returns>
FMatrix FMatrix::LookAtLH(const FVector& EyePosition, const FVector& FocusPoint, const FVector& WorldUp)
{
	FVector Forward = (FocusPoint - EyePosition).GetSafeNormal();
	FVector Right = FVector::CrossProduct(WorldUp, Forward).GetSafeNormal();
	FVector Up = FVector::CrossProduct(Forward, Right).GetSafeNormal();

	// row major
	FMatrix Result = FMatrix(
		FVector4(Right.X, Up.X, Forward.X, 0.0f),
		FVector4(Right.Y, Up.Y, Forward.Y, 0.0f),
		FVector4(Right.Z, Up.Z, Forward.Z, 0.0f),
		FVector4(-Right.Dot(EyePosition), -Up.Dot(EyePosition), -Forward.Dot(EyePosition), 1.0f)
	);

	return Result;
}

FMatrix FMatrix::PerspectiveFovLH(float FieldOfView, float AspectRatio, float NearPlane, float FarPlane)
{
	FMatrix Result;
	float YScale = 1.0f / tan(FieldOfView / 2.0f);
	float XScale = YScale / AspectRatio;
	Result.M[0][0] = XScale;
	Result.M[1][1] = YScale;
	Result.M[2][2] = FarPlane / (FarPlane - NearPlane);
	Result.M[2][3] = 1.0f;
	Result.M[3][2] = -NearPlane * FarPlane / (FarPlane - NearPlane);
	Result.M[3][3] = 0.0f;
	return Result;
}

FMatrix FMatrix::MakeFromDirection(const FVector& direction, const FVector& WorldUp) {
	FVector Forward = direction.GetSafeNormal();
	FVector Right = FVector::CrossProduct(WorldUp, Forward).GetSafeNormal();
	FVector Up = FVector::CrossProduct(Forward, Right).GetSafeNormal();

	FMatrix Result = FMatrix(
		FVector4(Forward.X, Right.X, Up.X, 0.f),
		FVector4(Forward.Y, Right.Y, Up.Y, 0.f),
		FVector4(Forward.Z, Right.Z, Up.Z, 0.f),
		FVector4(0.f, 0.f, 0.f, 1.f)
	);

	return FMatrix::Transpose(Result);
}

FVector FMatrix::GetTranslation() const
{
	return FVector(M[3][0], M[3][1], M[3][2]);
}

FVector FMatrix::GetScale() const
{
	float X = FVector(M[0][0], M[0][1], M[0][2]).Length();
	float Y = FVector(M[1][0], M[1][1], M[1][2]).Length();
	float Z = FVector(M[2][0], M[2][1], M[2][2]).Length();
	return { X, Y, Z };

	//return FVector(M[0][0], M[1][1], M[2][2]);
}

FVector FMatrix::GetRotation() const
{
	FQuat Q = FQuat::MakeFromRotationMatrix(*this);

	FVector Euler = Q.GetEuler();
	return Euler;
}

FVector FMatrix::TransformPositionVector(const FVector& Vector) const
{
	return {
			Vector.X * M[0][0] + Vector.Y * M[1][0] + Vector.Z * M[2][0] + M[3][0],
			Vector.X * M[0][1] + Vector.Y * M[1][1] + Vector.Z * M[2][1] + M[3][1],
			Vector.X * M[0][2] + Vector.Y * M[1][2] + Vector.Z * M[2][2] + M[3][2]
	};
}

FVector FMatrix::TransformDirectionVector(const FVector& Vector) const {
	return {
			Vector.X * M[0][0] + Vector.Y * M[1][0] + Vector.Z * M[2][0],
			Vector.X * M[0][1] + Vector.Y * M[1][1] + Vector.Z * M[2][1],
			Vector.X * M[0][2] + Vector.Y * M[1][2] + Vector.Z * M[2][2]
	};
}

FVector4 FMatrix::TransformVector4(const FVector4& Vector) const
{
	return {
			Vector.X * M[0][0] + Vector.Y * M[1][0] + Vector.Z * M[2][0] + Vector.W * M[3][0],
			Vector.X * M[0][1] + Vector.Y * M[1][1] + Vector.Z * M[2][1] + Vector.W * M[3][1],
			Vector.X * M[0][2] + Vector.Y * M[1][2] + Vector.Z * M[2][2] + Vector.W * M[3][2],
			Vector.X * M[0][3] + Vector.Y * M[1][3] + Vector.Z * M[2][3] + Vector.W * M[3][3]
	};
}

FTransform FMatrix::GetTransform() const
{
	FQuat RotationQuat = FQuat::MakeFromRotationMatrix(*this);
	return FTransform(GetTranslation(), RotationQuat, GetScale());
}

FMatrix FMatrix::RotateRoll(float Angle)
{
	Angle = FMath::DegreesToRadians(Angle);

	FMatrix Result;

	float C = cos(Angle);
	float S = sin(Angle);

	Result.M[1][1] = C;
	Result.M[1][2] = -S;
	Result.M[2][1] = S;
	Result.M[2][2] = C;

	return Result;
}

FMatrix FMatrix::RotatePitch(float Angle)
{
	Angle = FMath::DegreesToRadians(Angle);

	FMatrix Result;

	float C = cos(Angle);
	float S = sin(Angle);

	Result.M[0][0] = C;
	Result.M[0][2] = S;
	Result.M[2][0] = -S;
	Result.M[2][2] = C;
	return Result;
}

FMatrix FMatrix::RotateYaw(float Angle)
{
	Angle = FMath::DegreesToRadians(Angle);
	FMatrix Result;

	float C = cos(Angle);
	float S = sin(Angle);

	Result.M[0][0] = C;
	Result.M[0][1] = S;
	Result.M[1][0] = -S;
	Result.M[1][1] = C;

	return Result;
}

// TODO: 벡터 받아서 Rotate 해주는 것이니까 네이밍 제대로 해주기.
FMatrix FMatrix::RotateToMatrix(float X, float Y, float Z)
{
	if (abs(Y) == 90)
	{
		return RotateRoll(X) * RotatePitch(Y) * RotateYaw(Z);
	}
	return  RotateRoll(X) *  RotatePitch(Y) * RotateYaw(Z);
}
