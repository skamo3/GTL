
#pragma once
#include <cmath>

#define SMALL_NUMBER 1.e-8f
#define PI 3.1415926535897932384626433832795f
#define PI2 6.283185307179586476925286766559f

struct FVector
{
    /// <summary>
	/// X == Pitch, Y == Yaw, Z == Roll
    /// </summary>
    float X, Y, Z;

	// Vector(0, 0, 0)
	static const FVector ZeroVector;
	// Vector(1, 1, 1)
	static const FVector OneVector;
	// DirectX 기준 : Vector(0, 1, 0)
	static const FVector UpVector;
	// DirectX 기준 : Vector(0, -1, 0)
	static const FVector DownVector;
	// DirectX 기준 : Vector(0, 0, 1)
	static const FVector ForwardVector;
	// DirectX 기준 : Vector(0, 0, -1)
	static const FVector BackwardVector;
	// DirectX 기준 : Vector(1, 0, 0)
	static const FVector RightVector;
	// DirectX 기준 : Vector(-1, 0, 0)
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
		return 0.f;
	}
	inline float& operator[](int index)
	{
		if (index == 0) return X;
		if (index == 1) return Y;
		if (index == 2) return Z;
		return X;
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
	/// 이 벡터와 다른 벡터의 내적을 반환
    /// </summary>
    inline float Dot(const FVector& v) const
    {
        return X * v.X + Y * v.Y + Z * v.Z;
    }

    /// <summary>
	/// v1과 v2의 내적을 반환
    /// </summary>
    inline static float DotProduct(const FVector& v1, const FVector& v2)
    {
        return v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z;
    }
	
    /// <summary>
	/// 이 벡터와 다른 벡터의 외적을 반환
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
	/// v1과 v2의 외적을 반환
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
	/// 벡터 성분들을 절대값으로 변환
	/// </summary>
	inline FVector GetAbs() const
	{
		return FVector(std::abs(X), std::abs(Y), std::abs(Z));
	}

	/// <summary>
	/// x, y만 고려한 2D 벡터의 길이를 반환
	/// </summary>
	inline float Length2D() const
	{
		return sqrtf(X * X + Y * Y);
	}

    /// <summary>
	/// x, y만 고려한 2D 벡터의 길이의 제곱을 반환
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
	/// 정규화(길이가 1인)벡터로 변환)
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
	/// 벡터를 정규화된 단위 벡터(Unit Direction Vector)로 변환하고, 벡터의 원래 길이(Length)를 함께 반환합니다.
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
    /// 벡터를 Z축 기준으로 투영(XY 평면 위에 벡터를 Projection)한 벡터를 반환
    /// </summary>
    inline FVector Projection() const
    {
		const float RZ = 1.f / Z;
		return FVector(X * RZ, Y * RZ, 1.f);
    }

    /// <summary>
    /// 이 벡터의 각 성분에 대한 역수(1/src.X, 1/src.Y, 1/src.Z)를 반환
    /// </summary>
    static bool Reciprocal(const FVector& src, FVector& dst);
};


// 비멤버 오퍼레이터: float * FVector
inline FVector operator*(float s, const FVector& v)
{
	return FVector(v.X * s, v.Y * s, v.Z * s);
}