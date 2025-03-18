
#pragma once
#include <cmath>
#include "MathFwd.h"

struct FMath
{
    /** A와 B중에 더 작은 값을 반환합니다. */
    template <typename T>
    [[nodiscard]] static inline constexpr T Min(const T A, const T B)
    {
        return A < B ? A : B;
    }

    /** A와 B중에 더 큰 값을 반환합니다. */
    template <typename T>
    [[nodiscard]] static inline constexpr T Max(const T A, const T B)
    {
        return B < A ? A : B;
    }

    /** X를 Min과 Max의 사이의 값으로 클램핑 합니다. */
    template <typename T>
    [[nodiscard]] static inline constexpr T Clamp(const T X, const T MinValue, const T MaxValue)
    {
        return Max(Min(X, MaxValue), MinValue);
    }

    /** A의 절댓값을 구합니다. */
    template <typename T>
    [[nodiscard]] static inline constexpr T Abs(const T A)
    {
        return A < T(0) ? -A : A;
    }

    /** A의 제곱을 구합니다. */
    template <typename T>
    [[nodiscard]] static inline constexpr T Pow(const T A)
    {
        return A * A;
    }

    // A의 제곱근을 구합니다.
    [[nodiscard]] static inline float Sqrt(float A) { return sqrtf(A); }
    [[nodiscard]] static inline double Sqrt(double A) { return sqrt(A); }

    /** A의 역제곱근을 구합니다. */
    [[nodiscard]] static inline float InvSqrt(float A) { return 1.0f / sqrtf(A); }
    [[nodiscard]] static inline double InvSqrt(double A) { return 1.0 / sqrt(A); }

    /** A와 B를 Alpha값에 따라 선형으로 보간합니다. */
    template <typename T>
    [[nodiscard]] static inline constexpr T Lerp(const T& A, const T& B, float Alpha)
    {
        return static_cast<T>((A * (1.0f - Alpha)) + (B * Alpha));
    }

    /** A와 B를 Alpha값에 따라 선형으로 보간합니다. */
    template <typename T>
    [[nodiscard]] static inline constexpr T Lerp(const T& A, const T& B, double Alpha)
    {
        return static_cast<T>((A * (1.0 - Alpha)) + (B * Alpha));
    }

    template <typename T>
    [[nodiscard]] static inline constexpr auto RadiansToDegrees(const T& RadVal) -> decltype(RadVal* (180.0f / PI))
    {
        return RadVal * (180.0f / PI);
    }

    [[nodiscard]] static inline constexpr float RadiansToDegrees(float RadVal)
    {
        return RadVal * (180.0f / PI);
    }

    [[nodiscard]] static inline constexpr double RadiansToDegrees(double RadVal)
    {
        return RadVal * (180.0 / PI_DOUBLE);
    }

    template <typename T>
    [[nodiscard]] static inline constexpr auto DegreesToRadians(const T& DegVal) -> decltype(DegVal* (PI / 180.0f))
    {
        return DegVal * (PI / 180.0f);
    }

    [[nodiscard]] static inline constexpr float DegreesToRadians(float DegVal)
    {
        return DegVal * (PI / 180.0f);
    }

    [[nodiscard]] static inline constexpr double DegreesToRadians(double DegVal)
    {
        return DegVal * (PI_DOUBLE / 180.0);
    }

    [[nodiscard]] static inline double Cos(double RadVal)
    {
        return cos(RadVal);
    }

    [[nodiscard]] static inline float Cos(float RadVal)
    {
        return cosf(RadVal);
    }
    [[nodiscard]] static inline double Sin(double RadVal)
    {
        return sin(RadVal);
    }
    [[nodiscard]] static inline float Sin(float RadVal)
    {
        return sinf(RadVal);
    }
    [[nodiscard]] static inline double Tan(double RadVal)
    {
        return tan(RadVal);
    }
    [[nodiscard]] static inline float Tan(float RadVal)
    {
        return tanf(RadVal);
    }
    [[nodiscard]] static inline double Acos(double Value)
    {
        return acos(Value);
    }
    [[nodiscard]] static inline float Acos(float Value)
    {
        return acosf(Value);
    }
    [[nodiscard]] static inline double Asin(double Value)
    {
        return asin(Value);
    }
    [[nodiscard]] static inline float Asin(float Value)
    {
        return asinf(Value);
    }
    [[nodiscard]] static inline double Atan(double Value)
    {
        return atan(Value);
    }
    [[nodiscard]] static inline float Atan(float Value)
    {
        return atanf(Value);
    }
    [[nodiscard]] static inline double Atan2(double Y, double X)
    {
        return atan2(Y, X);
    }
    [[nodiscard]] static inline float Atan2(float Y, float X)
    {
        return atan2f(Y, X);
    }
    [[nodiscard]] static inline void SinCos(float* ScalarSin, float* ScalarCos, float Value)
    {
		*ScalarSin = sinf(Value);
		*ScalarCos = cosf(Value);
	}
	[[nodiscard]] static inline void SinCos(double* ScalarSin, double* ScalarCos, double Value)
	{
		*ScalarSin = sin(Value);
		*ScalarCos = cos(Value);
    }
    [[nodiscard]] static inline float UnwindDegrees(float A)
    {
		while (A > 180.0f)
		{
			A -= 360.0f;
		}
        while (A < -180.0f)
        {
            A += 360.0f;
        }
		return A;
    }

    template <typename T>
    [[nodiscard]] static inline T Square(T Value)
    {
        return Value * Value;
    }

};