#pragma once
#include "Quaternion.h"

struct alignas(16) FMatrix
{
	alignas(16) float M[4][4];
	static const FMatrix Identity;

public:
	FMatrix();
	FMatrix(const FMatrix& other);
	FMatrix(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	inline void SetIdentity()
	{
		M[0][0] = 1; M[0][1] = 0;  M[0][2] = 0;  M[0][3] = 0;
		M[1][0] = 0; M[1][1] = 1;  M[1][2] = 0;  M[1][3] = 0;
		M[2][0] = 0; M[2][1] = 0;  M[2][2] = 1;  M[2][3] = 0;
		M[3][0] = 0; M[3][1] = 0;  M[3][2] = 0;  M[3][3] = 1;
	}

	inline FMatrix operator*(const FMatrix& other) const
	{
		FMatrix result;

		// (row 0)
		result.M[0][0] = M[0][0] * other.M[0][0] + M[0][1] * other.M[1][0] + M[0][2] * other.M[2][0] + M[0][3] * other.M[3][0];
		result.M[0][1] = M[0][0] * other.M[0][1] + M[0][1] * other.M[1][1] + M[0][2] * other.M[2][1] + M[0][3] * other.M[3][1];
		result.M[0][2] = M[0][0] * other.M[0][2] + M[0][1] * other.M[1][2] + M[0][2] * other.M[2][2] + M[0][3] * other.M[3][2];
		result.M[0][3] = M[0][0] * other.M[0][3] + M[0][1] * other.M[1][3] + M[0][2] * other.M[2][3] + M[0][3] * other.M[3][3];

		// (row 1)
		result.M[1][0] = M[1][0] * other.M[0][0] + M[1][1] * other.M[1][0] + M[1][2] * other.M[2][0] + M[1][3] * other.M[3][0];
		result.M[1][1] = M[1][0] * other.M[0][1] + M[1][1] * other.M[1][1] + M[1][2] * other.M[2][1] + M[1][3] * other.M[3][1];
		result.M[1][2] = M[1][0] * other.M[0][2] + M[1][1] * other.M[1][2] + M[1][2] * other.M[2][2] + M[1][3] * other.M[3][2];
		result.M[1][3] = M[1][0] * other.M[0][3] + M[1][1] * other.M[1][3] + M[1][2] * other.M[2][3] + M[1][3] * other.M[3][3];

		//  (row 2)
		result.M[2][0] = M[2][0] * other.M[0][0] + M[2][1] * other.M[1][0] + M[2][2] * other.M[2][0] + M[2][3] * other.M[3][0];
		result.M[2][1] = M[2][0] * other.M[0][1] + M[2][1] * other.M[1][1] + M[2][2] * other.M[2][1] + M[2][3] * other.M[3][1];
		result.M[2][2] = M[2][0] * other.M[0][2] + M[2][1] * other.M[1][2] + M[2][2] * other.M[2][2] + M[2][3] * other.M[3][2];
		result.M[2][3] = M[2][0] * other.M[0][3] + M[2][1] * other.M[1][3] + M[2][2] * other.M[2][3] + M[2][3] * other.M[3][3];

		// (row 3)
		result.M[3][0] = M[3][0] * other.M[0][0] + M[3][1] * other.M[1][0] + M[3][2] * other.M[2][0] + M[3][3] * other.M[3][0];
		result.M[3][1] = M[3][0] * other.M[0][1] + M[3][1] * other.M[1][1] + M[3][2] * other.M[2][1] + M[3][3] * other.M[3][1];
		result.M[3][2] = M[3][0] * other.M[0][2] + M[3][1] * other.M[1][2] + M[3][2] * other.M[2][2] + M[3][3] * other.M[3][2];
		result.M[3][3] = M[3][0] * other.M[0][3] + M[3][1] * other.M[1][3] + M[3][2] * other.M[2][3] + M[3][3] * other.M[3][3];

		return result;
	}
	inline void operator*=(const FMatrix& other)
	{
		*this = (*this) * other;
	}

	inline FMatrix operator*(const float s) const
	{
		FMatrix result;

		for (int i = 0; i < 4; i++)
		{
			result.M[i][0] = M[i][0] * s;
			result.M[i][1] = M[i][1] * s;
			result.M[i][2] = M[i][2] * s;
			result.M[i][3] = M[i][3] * s;
		}

		return result;
	}
	inline void operator*=(const float s)
	{
		*this = *this * s;
	}

	inline FMatrix operator+(const FMatrix& other) const
	{
		FMatrix result;
		for (int i = 0; i < 4; i++)
		{
			result.M[i][0] = M[i][0] + other.M[i][0];
			result.M[i][1] = M[i][1] + other.M[i][1];
			result.M[i][2] = M[i][2] + other.M[i][2];
			result.M[i][3] = M[i][3] + other.M[i][3];
		}
		return result;
	}
	inline void operator+=(const FMatrix& other)
	{
		*this = *this + other;
	}

	inline FMatrix operator-(const FMatrix& other) const
	{
		FMatrix result;
		for (int i = 0; i < 4; i++)
		{
			result.M[i][0] = M[i][0] - other.M[i][0];
			result.M[i][1] = M[i][1] - other.M[i][1];
			result.M[i][2] = M[i][2] - other.M[i][2];
			result.M[i][3] = M[i][3] - other.M[i][3];
		}
		return result;
	}
	inline void operator-=(const FMatrix& other)
	{
		*this = *this - other;
	}

	inline bool operator==(const FMatrix& other) const
	{
		for (int i = 0; i < 4; i++)
		{
			if (M[i][0] != other.M[i][0] || M[i][1] != other.M[i][1] || M[i][2] != other.M[i][2] || M[i][3] != other.M[i][3])
			{
				return false;
			}
		}
		return true;
	}
	inline bool operator!=(const FMatrix& other) const
	{
		return !(*this == other);
	}

	/// <summary>
	/// 주어진 3차원 벡터에 대해 투영 변환을 수행
	/// </summary>
	/// <param name="inW">행렬 곱셈에 사용될 입력 w 값입니다. 0을 전달하면 방향 벡터를 변환, 1을 전달하면 위치 벡터를 변환</param>
	/// <param name="outW">행렬 곱셈 수행 결과로 나온 w 값이 저장 원근 분할을 할 경우 결과 Vecotr에 w를 나눠줘야함 </param>
	FVector ProjectVector(const FVector& v, float inW, float& outW) const;

	/// <summary>
	/// 입력 벡터를 (v.X, v.Y, v.Z, 1)로 취급하여, 현재 행렬과의 곱셈 결과로 변환된 3차원 좌표를 반환
	/// </summary>
	FVector AffineTransform(const FVector& v) const;

	inline FMatrix GetTranspose() const
	{
		FMatrix result;

		result.M[0][0] = M[0][0]; 	result.M[1][0] = M[0][1]; 	result.M[2][0] = M[0][2];	result.M[3][0] = M[0][3];
		result.M[0][1] = M[1][0]; 	result.M[1][1] = M[1][1];   result.M[2][1] = M[1][2];	result.M[3][1] = M[1][3];
		result.M[0][2] = M[2][0]; 	result.M[1][2] = M[2][1];	result.M[2][2] = M[2][2];	result.M[3][2] = M[2][3];
		result.M[0][3] = M[3][0];	result.M[1][3] = M[3][1];	result.M[2][3] = M[3][2];	result.M[3][3] = M[3][3];

		return result;
	}


	inline float Determinant() const
	{
		float det = M[0][0] *  // M[0][0]
			(
				M[1][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2])
				- M[1][2] * (M[2][1] * M[3][3] - M[2][3] * M[3][1])
				+ M[1][3] * (M[2][1] * M[3][2] - M[2][2] * M[3][1])
				)
			- M[0][1] *  // M[0][1]
			(
				M[1][0] * (M[2][2] * M[3][3] - M[2][3] * M[3][2])
				- M[1][2] * (M[2][0] * M[3][3] - M[2][3] * M[3][0])
				+ M[1][3] * (M[2][0] * M[3][2] - M[2][2] * M[3][0])
				)
			+ M[0][2] *  // M[0][2]
			(
				M[1][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1])
				- M[1][1] * (M[2][0] * M[3][3] - M[2][3] * M[3][0])
				+ M[1][3] * (M[2][0] * M[3][1] - M[2][1] * M[3][0])
				)
			- M[0][3] *  // M[0][3]
			(
				M[1][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1])
				- M[1][1] * (M[2][0] * M[3][2] - M[2][2] * M[3][0])
				+ M[1][2] * (M[2][0] * M[3][1] - M[2][1] * M[3][0])
				);

		return det;
	}

	static bool Inverse(const FMatrix& src, FMatrix& dst);

	inline FMatrix RotationAdjoint() const
	{
		FMatrix ta;

		ta.M[0][0] = M[1][1] * M[2][2] - M[1][2] * M[2][1];
		ta.M[0][1] = M[1][2] * M[2][0] - M[1][0] * M[2][2];
		ta.M[0][2] = M[1][0] * M[2][1] - M[1][1] * M[2][0];
		ta.M[0][3] = 0.f;

		ta.M[1][0] = M[2][1] * M[0][2] - M[2][2] * M[0][1];
		ta.M[1][1] = M[2][2] * M[0][0] - M[2][0] * M[0][2];
		ta.M[1][2] = M[2][0] * M[0][1] - M[2][1] * M[0][0];
		ta.M[1][3] = 0.f;

		ta.M[2][0] = M[0][1] * M[1][2] - M[0][2] * M[1][1];
		ta.M[2][1] = M[0][2] * M[1][0] - M[0][0] * M[1][2];
		ta.M[2][2] = M[0][0] * M[1][1] - M[0][1] * M[1][0];
		ta.M[2][3] = 0.f;

		ta.M[3][0] = 0.f;
		ta.M[3][1] = 0.f;
		ta.M[3][2] = 0.f;
		ta.M[3][3] = 1.f;

		return ta;
	}

	FVector GetScaleVector() const;

	inline void RemoveScaling()
	{
		const float squareSum0 = (M[0][0] * M[0][0]) + (M[0][1] * M[0][1]) + (M[0][2] * M[0][2]);
		const float squareSum1 = (M[1][0] * M[1][0]) + (M[1][1] * M[1][1]) + (M[1][2] * M[1][2]);
		const float squareSum2 = (M[2][0] * M[2][0]) + (M[2][1] * M[2][1]) + (M[2][2] * M[2][2]);

		const float scale0 = squareSum0 >= 0.f ? squareSum0 : 1;
		const float scale1 = squareSum1 >= 0.f ? sqrtf(squareSum1) : 1;
		const float scale2 = squareSum2 >= 0.f ? sqrtf(squareSum2) : 1;

		M[0][0] *= scale0; M[0][1] *= scale0; M[0][2] *= scale0;
		M[1][0] *= scale1; M[1][1] *= scale1; M[1][2] *= scale1;
		M[2][0] *= scale2; M[2][1] *= scale2; M[2][2] *= scale2;
	}

	FMatrix GetMatrixWithOutScale() const;

	inline FMatrix RemoveTranslation() const
	{
		FMatrix result = *this;

		result.M[3][0] = 0.f;
		result.M[3][1] = 0.f;
		result.M[3][2] = 0.f;

		return result;
	}

	FMatrix AppendTranslation(const FVector& translation) const;


	inline FMatrix ApplyScale(const float scale) const
	{
		FMatrix sacleMatrix(
			scale, 0, 0, 0,
			0, scale, 0, 0,
			0, 0, scale, 0,
			0, 0, 0, 1
		);

		return sacleMatrix * (*this);
	}

	inline FMatrix ApplyScale(const FVector& scale) const
	{
		FMatrix sacleMatrix(
			scale.X, 0, 0, 0,
			0, scale.Y, 0, 0,
			0, 0, scale.Z, 0,
			0, 0, 0, 1
		);
		return sacleMatrix * (*this);
	}

	static FMatrix CreateRotationX(float angle);

	static FMatrix CreateRotationY(float angle);

	static FMatrix CreateRotationZ(float angle);

	static FMatrix CreateRotationXYZ(const FVector& rotation);

	static FMatrix CreateRotationQuat(const FQuaternion& q);

	inline void Rotate(const FVector& Rotation)
	{
		FMatrix rotMat = CreateRotationXYZ(Rotation);

		*this *= rotMat;
	}

	static FMatrix CreateScaleMatrix(float scale);

	static FMatrix CreateScaleMatrix(const FVector& scale);

	inline void ScaleTranslation(FVector& inScale3D)
	{
		M[3][0] *= inScale3D.X;
		M[3][1] *= inScale3D.Y;
		M[3][2] *= inScale3D.Z;
	}


	inline void GetScaledAxes(FVector& X, FVector& Y, FVector& Z) const
	{
		X.X = M[0][0]; X.Y = M[0][1]; X.Z = M[0][2];
		Y.X = M[1][0]; Y.Y = M[1][1]; Y.Z = M[1][2];
		Z.X = M[2][0]; Z.Y = M[2][1]; Z.Z = M[2][2];
	}

	inline void GetUnitAxes(FVector& X, FVector& Y, FVector& Z) const
	{
		GetScaledAxes(X, Y, Z);
		X.GetNormalizedVector();
		Y.GetNormalizedVector();
		Z.GetNormalizedVector();
	}

	inline void SetAxis(int i, const FVector& axis)
	{
		M[i][0] = axis.X;
		M[i][1] = axis.Y;
		M[i][2] = axis.Z;
	}

	inline void SetAxes(FVector& XAxis, FVector& YAxis, FVector& ZAxis, FVector& Origin)
	{
		SetAxis(0, XAxis);
		SetAxis(1, YAxis);
		SetAxis(2, ZAxis);
		SetOrigin(Origin);
	}

	inline FVector GetOrigin() const
	{
		return FVector(M[3][0], M[3][1], M[3][2]);
	}

	inline void SetOrigin(const FVector& newOrigin)
	{
		M[3][0] = newOrigin.X;
		M[3][1] = newOrigin.Y;
		M[3][2] = newOrigin.Z;
	}

	static FMatrix CreateBasisMatrix(const FVector& xAxis, const FVector& yAxis, const FVector& zAxis, const FVector& origin);

	static FMatrix CreateTranslationMatrix(const FVector& location);

	inline FVector GetColumn(int i) const
	{
		return FVector(M[0][i], M[1][i], M[2][i]);
	}

	inline void SetColumn(int i, const FVector& v)
	{
		M[0][i] = v.X;
		M[1][i] = v.Y;
		M[2][i] = v.Z;
	}

	inline FVector GetRow(int i) const
	{
		return FVector(M[i][0], M[i][1], M[i][2]);
	}

	inline void SetRow(int i, const FVector& v)
	{
		M[i][0] = v.X;
		M[i][1] = v.Y;
		M[i][2] = v.Z;
	}

	inline FVector GetForwardVector() const
	{
		return GetRow(2).GetNormalizedVector();
	}

	inline FVector GetRightVector() const
	{
		return GetRow(0).GetNormalizedVector();
	}

	inline FVector GetUpVector() const
	{
		return GetRow(1).GetNormalizedVector();
	}

	static FMatrix CreateLookToMatrixLeftHand(const FVector& eye, const FVector& toDir, const FVector& up);

	static FMatrix CreateLookToMatrixRightHand(const FVector& eye, const FVector& toDir, const FVector& up);

	static FMatrix CreateOrthographicProjectionMatrixLeftHand(float screenWidth, float screenHeight, float zNear, float zFar);

	static FMatrix CreateOrthographicProjectionMatrixRightHand(float screenWidth, float screenHeight, float zNear, float zFar);

	static FMatrix CreatePerspectiveProjectionMatrixLeftHand(float fov, float aspectRatio, float zNear, float zFar);

	static FMatrix CreatePerspectiveProjectionMatrixRightHand(float fov, float aspectRatio, float zNear, float zFar);
};