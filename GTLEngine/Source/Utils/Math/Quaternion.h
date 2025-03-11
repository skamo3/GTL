#pragma once
#include "Vector.h"
struct FQuaternion
{
	float X, Y, Z, W;
	FQuaternion() : X(0), Y(0), Z(0), W(1) {}
	FQuaternion(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}
	FQuaternion(const FQuaternion& q) : X(q.X), Y(q.Y), Z(q.Z), W(q.W) {}

	FQuaternion(const FVector& axis, float angle)
	{
		float halfAngle = angle * 0.5f;
		float s = sin(halfAngle);
		X = axis.X * s;
		Y = axis.Y * s;
		Z = axis.Z * s;
		W = cos(halfAngle);
	}

	FQuaternion(const FVector& euler)
	{
		// 도 -> 라디안 변환
		float radRoll = euler.Z * (PI / 180.0f);
		float radPitch = euler.X * (PI / 180.0f);;
		float radYaw = euler.Y * (PI / 180.0f);

		// 반각 계산
		float halfRoll = radRoll / 2.0f;
		float halfPitch = radPitch / 2.0f;
		float halfYaw = radYaw / 2.0f;

		// 사인, 코사인 계산
		float cr = cos(halfRoll);
		float sr = sin(halfRoll);
		float cp = cos(halfPitch);
		float sp = sin(halfPitch);
		float cy = cos(halfYaw);
		float sy = sin(halfYaw);

		W = cr * cy * cp + sr * sy * sp;
		X = cr * cy * sp - sr * sy * cp;
		Y = cr * sy * cp + sr * cy * sp;
		Z = sr * cy * cp - cr * sy * sp;
	}

	inline bool operator==(const FQuaternion& q) const
	{
		return X == q.X && Y == q.Y && Z == q.Z && W == q.W;
	}

	inline bool operator!=(const FQuaternion& q) const
	{
		return X != q.X || Y != q.Y || Z != q.Z || W != q.W;
	}


	FQuaternion operator*(const FQuaternion& q) const
	{
		return FQuaternion(
			W * q.X + X * q.W + Y * q.Z - Z * q.Y,
			W * q.Y + Y * q.W + Z * q.X - X * q.Z,
			W * q.Z + Z * q.W + X * q.Y - Y * q.X,
			W * q.W - X * q.X - Y * q.Y - Z * q.Z
		);
	}
	FQuaternion operator*(float s) const
	{
		return FQuaternion(X * s, Y * s, Z * s, W * s);
	}
	FQuaternion operator+(const FQuaternion& q) const
	{
		return FQuaternion(X + q.X, Y + q.Y, Z + q.Z, W + q.W);
	}
	FQuaternion operator-(const FQuaternion& q) const
	{
		return FQuaternion(X - q.X, Y - q.Y, Z - q.Z, W - q.W);
	}
	FQuaternion operator-() const
	{
		return FQuaternion(-X, -Y, -Z, -W);
	}
	FQuaternion& operator*=(const FQuaternion& q)
	{
		*this = *this * q;
		return *this;
	}
	FQuaternion& operator*=(float s)
	{
		X *= s;
		Y *= s;
		Z *= s;
		W *= s;
		return *this;
	}
	FQuaternion& operator+=(const FQuaternion& q)
	{
		X += q.X;
		Y += q.Y;
		Z += q.Z;
		W += q.W;
		return *this;
	}
	FQuaternion& operator-=(const FQuaternion& q)
	{
		X -= q.X;
		Y -= q.Y;
		Z -= q.Z;
		W -= q.W;
		return *this;
	}
	FQuaternion& operator=(const FQuaternion& q)
	{
		X = q.X;
		Y = q.Y;
		Z = q.Z;
		W = q.W;
		return *this;
	}

	inline FQuaternion GetNormalizeQuaternion() const
	{
		float norm = sqrtf(X * X + Y * Y + Z * Z + W * W);
		if (norm < SMALL_NUMBER)
		{
			return FQuaternion(0, 0, 0, 1);
		}
		float invNorm = 1.0f / norm;
		return FQuaternion(X * invNorm, Y * invNorm, Z * invNorm, W * invNorm);
	}
};
