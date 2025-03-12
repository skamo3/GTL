
#pragma once
#include <cmath>

#define SMALL_NUMBER 1.e-8f
#define PI 3.1415926535897932384626433832795f
#define PI2 6.283185307179586476925286766559f

struct FVector
{
	float X, Y, Z;

	// Vector(0, 0, 0)
	static const FVector ZeroVector;
	// Vector(1, 1, 1)
	static const FVector OneVector;
	// Vector(0, 0, 1)
	static const FVector UpVector;
	// Vector(0, 0, -1)
	static const FVector DownVector;
	// Vector(1, 0, 0)
	static const FVector ForwardVector;
	// Vector(1, 0, 0)
	static const FVector BackwardVector;
	// Vector(0, 1, 0)
	static const FVector RightVector;
	// Vector(0, -1, 0)
	static const FVector LeftVector;

	// Unit X Axis Vector (1, 0, 0)
	static const FVector XAxisVector;
	// Unit Y Axis Vector (0, 1, 0)
	static const FVector YAxisVector;
	// Unit Z Axis Vector (0, 0, 1)
	static const FVector ZAxisVector;

	static inline FVector Zero() { return ZeroVector; }
	static inline FVector One() { return OneVector; }

	static inline FVector UnitX() { return XAxisVector; }
	static inline FVector UnitY() { return YAxisVector; }
	static inline FVector UnitZ() { return ZAxisVector; }

	FVector(float _x = 0, float _y = 0, float _z = 0) : X(_x), Y(_y), Z(_z) {}

	inline FVector operator+(const FVector& v) const
	{
		return FVector(X + v.X, Y + v.Y, Z + v.Z);
	}

	inline FVector operator+=(const FVector& v)
	{
		X += v.X; Y += v.Y; Z += v.Z;
		return *this;
	}

	inline FVector operator-(const FVector& v) const
	{
		return FVector(X - v.X, Y - v.Y, Z - v.Z);
	}

	inline FVector operator-=(const FVector& v)
	{
		X -= v.X; Y -= v.Y; Z -= v.Z;
		return *this;
	}

	inline FVector operator-() const
	{
		return FVector(-X, -Y, -Z);
	}

	inline FVector operator*(const float s) const
	{
		return FVector(X * s, Y * s, Z * s);
	}

	inline FVector operator*=(const float s)
	{
		X *= s; Y *= s; Z *= s;
		return *this;
	}

	inline FVector operator/(const float s) const
	{
		return FVector(X / s, Y / s, Z / s);
	}

	inline FVector operator/=(const float s)
	{
		X /= s; Y /= s; Z /= s;
		return *this;
	}

	inline FVector operator/(const FVector& v) const
	{
		return FVector(X / v.X, Y / v.Y, Z / v.Z);
	}
	inline FVector operator/=(const FVector& v)
	{
		X /= v.X; Y /= v.Y; Z /= v.Z;
		return *this;
	}

	inline bool operator==(const FVector& v) const
	{
		return X == v.X && Y == v.Y && Z == v.Z;
	}

	inline bool operator!=(const FVector& v) const
	{
		return X != v.X || Y != v.Y || Z != v.Z;
	}

	inline float operator[](int index) const
	{
		if (index == 0) return X;
		if (index == 1) return Y;
		if (index == 2) return Z;
	}
	inline float& operator[](int index)
	{
		if (index == 0) return X;
		if (index == 1) return Y;
		if (index == 2) return Z;
	}

	inline float Length() const
	{
		return sqrtf(X * X + Y * Y + Z * Z);
	}

	inline float SquaredLength() const
	{
		return X * X + Y * Y + Z * Z;
	}

	/// <summary>
	/// �� ���Ϳ� �ٸ� ������ ������ ��ȯ
	/// </summary>
	inline float Dot(const FVector& v) const
	{
		return X * v.X + Y * v.Y + Z * v.Z;
	}

	/// <summary>
	/// v1�� v2�� ������ ��ȯ
	/// </summary>
	inline static float DotProduct(const FVector& v1, const FVector& v2)
	{
		return v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z;
	}

	/// <summary>
	/// �� ���Ϳ� �ٸ� ������ ������ ��ȯ
	/// </summary>
	inline FVector Cross(const FVector& v) const
	{
		return FVector(
			Y * v.Z - Z * v.Y,
			Z * v.X - X * v.Z,
			X * v.Y - Y * v.X
		);
	}

	/// <summary>
	/// v1�� v2�� ������ ��ȯ
	/// </summary>
	inline static FVector CrossProduct(const FVector& v1, const FVector& v2)
	{
		return FVector(
			v1.Y * v2.Z - v1.Z * v2.Y,
			v1.Z * v2.X - v1.X * v2.Z,
			v1.X * v2.Y - v1.Y * v2.X
		);
	}

	inline void Set(float _x, float _y, float _z)
	{
		X = _x; Y = _y; Z = _z;
	}

	/// <summary>
	/// ���� ���е��� ���밪���� ��ȯ
	/// </summary>
	inline FVector GetAbs() const
	{
		return FVector(std::abs(X), std::abs(Y), std::abs(Z));
	}

	/// <summary>
	/// x, y�� ����� 2D ������ ���̸� ��ȯ
	/// </summary>
	inline float Length2D() const
	{
		return sqrtf(X * X + Y * Y);
	}

	/// <summary>
	/// x, y�� ����� 2D ������ ������ ������ ��ȯ
	/// </summary>
	inline float SquaredLength2D() const
	{
		return X * X + Y * Y;
	}

	inline bool IsZero() const
	{
		return X == 0.f && Y == 0.f && Z == 0.f;
	}

	/// <summary>
	/// ����ȭ(���̰� 1��)���ͷ� ��ȯ)
	/// </summary>
	inline FVector GetNormalizedVector() const
	{
		float len = Length();
		if (len < SMALL_NUMBER)
		{
			return FVector(0.f, 0.f, 0.f);
		}
		return FVector(X / len, Y / len, Z / len);
	}

	/// <summary>
	/// ���͸� ����ȭ�� ���� ����(Unit Direction Vector)�� ��ȯ�ϰ�, ������ ���� ����(Length)�� �Բ� ��ȯ�մϴ�.
	/// </summary>
	void ToDirectionAndLength(FVector& outDir, float& outLength)
	{
		outLength = Length();
		if (outLength < SMALL_NUMBER)
		{
			outDir = FVector::ZeroVector;
		}
		else
		{
			float invLength = 1.f / outLength;
			outDir = FVector(X * invLength, Y * invLength, Z * invLength);
		}
	}

	/// <summary>
	/// ���͸� Z�� �������� ����(XY ��� ���� ���͸� Projection)�� ���͸� ��ȯ
	/// </summary>
	inline FVector Projection() const
	{
		const float RZ = 1.f / Z;
		return FVector(X * RZ, Y * RZ, 1.f);
	}

	/// <summary>
	/// �� ������ �� ���п� ���� ����(1/src.X, 1/src.Y, 1/src.Z)�� ��ȯ
	/// </summary>
	static bool Reciprocal(const FVector& src, FVector& dst);
};


// 비멤버 오퍼레이터: float * FVector
inline FVector operator*(float s, const FVector& v)
{
	return FVector(v.X * s, v.Y * s, v.Z * s);
}