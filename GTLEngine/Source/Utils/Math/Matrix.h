#pragma once
#include <Math/MathFwd.h>

struct alignas(16) FMatrix
{
	alignas(16) float M[4][4];
	static const FMatrix Identity;

public:
	/// <summary>
	/// 기본 생성자는 단위 행렬로 초기화합니다.
	/// </summary>
	FMatrix();
	FMatrix(const FMatrix& other);
	FMatrix(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);


	/// <summary>
	/// 현재 행렬을 단위 행렬(DirectX 기준 : 월드 좌표계)로 설정
	/// </summary>
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

		// 첫 번째 행
		result.M[0][0] = M[0][0] * other.M[0][0] + M[0][1] * other.M[1][0] + M[0][2] * other.M[2][0] + M[0][3] * other.M[3][0];
		result.M[0][1] = M[0][0] * other.M[0][1] + M[0][1] * other.M[1][1] + M[0][2] * other.M[2][1] + M[0][3] * other.M[3][1];
		result.M[0][2] = M[0][0] * other.M[0][2] + M[0][1] * other.M[1][2] + M[0][2] * other.M[2][2] + M[0][3] * other.M[3][2];
		result.M[0][3] = M[0][0] * other.M[0][3] + M[0][1] * other.M[1][3] + M[0][2] * other.M[2][3] + M[0][3] * other.M[3][3];

		// 두 번째 행
		result.M[1][0] = M[1][0] * other.M[0][0] + M[1][1] * other.M[1][0] + M[1][2] * other.M[2][0] + M[1][3] * other.M[3][0];
		result.M[1][1] = M[1][0] * other.M[0][1] + M[1][1] * other.M[1][1] + M[1][2] * other.M[2][1] + M[1][3] * other.M[3][1];
		result.M[1][2] = M[1][0] * other.M[0][2] + M[1][1] * other.M[1][2] + M[1][2] * other.M[2][2] + M[1][3] * other.M[3][2];
		result.M[1][3] = M[1][0] * other.M[0][3] + M[1][1] * other.M[1][3] + M[1][2] * other.M[2][3] + M[1][3] * other.M[3][3];

		// 세 번째 행
		result.M[2][0] = M[2][0] * other.M[0][0] + M[2][1] * other.M[1][0] + M[2][2] * other.M[2][0] + M[2][3] * other.M[3][0];
		result.M[2][1] = M[2][0] * other.M[0][1] + M[2][1] * other.M[1][1] + M[2][2] * other.M[2][1] + M[2][3] * other.M[3][1];
		result.M[2][2] = M[2][0] * other.M[0][2] + M[2][1] * other.M[1][3] + M[2][2] * other.M[2][2] + M[2][3] * other.M[3][2];
		result.M[2][3] = M[2][0] * other.M[0][3] + M[2][1] * other.M[1][3] + M[2][2] * other.M[2][3] + M[2][3] * other.M[3][3];

		// 네 번째 행
		result.M[3][0] = M[3][0] * other.M[0][0] + M[3][1] * other.M[1][0] + M[3][2] * other.M[2][0] + M[3][3] * other.M[3][0];
		result.M[3][1] = M[3][0] * other.M[0][1] + M[3][1] * other.M[1][1] + M[3][2] * other.M[2][1] + M[3][3] * other.M[3][1];
		result.M[3][2] = M[3][0] * other.M[0][2] + M[3][1] * other.M[1][3] + M[3][2] * other.M[2][3] + M[3][3] * other.M[3][3];
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

	/// <summary>
	/// 현재 4x4 행렬을 전치(행과 열을 뒤 바꾼)한 새 FMatrix를 반환 
	/// </summary>
	inline FMatrix GetTranspose() const
	{
		FMatrix result;

		result.M[0][0] = M[0][0]; 	result.M[1][0] = M[0][1]; 	result.M[2][0] = M[0][2];	result.M[3][0] = M[0][3];
		result.M[0][1] = M[1][0]; 	result.M[1][1] = M[1][1];   result.M[2][1] = M[1][2];	result.M[3][1] = M[1][3];
		result.M[0][2] = M[2][0]; 	result.M[1][2] = M[2][1];	result.M[2][2] = M[2][2];	result.M[3][2] = M[2][3];
		result.M[0][3] = M[3][0];	result.M[1][3] = M[3][1];	result.M[2][3] = M[3][2];	result.M[3][3] = M[3][3];

		return result;
	}

	/// <summary>
	/// 현재 4x4 행렬의 행렬식(정사각 행렬에 스칼라를 대응시키는 함수)을 계산하여 반환
	/// </summary>
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

	/// <summary>
	/// 4x4 행렬 src의 역행렬(src*dst = Identity)을 구해 dst에 저장합니다.
	/// 만약 역행렬이 존재하지 않으면(determinant가 0에 가깝게 작은 경우) false를 반환
	/// </summary>
	/// <param name="src">역행렬을 구할 소스 행렬</param>
	/// <param name="dst">결과로 얻을 역행렬을 저장할 대상</param>
	/// <returns>역행렬을 구할 수 있으면 true, 아니면 false</returns>
	static bool Inverse(const FMatrix& src, FMatrix& dst);

	/// <summary>
	/// 3×3 행렬식 계산 (m의 지정한 세 행과 세 열에 대한 3×3 행렬식)
	/// </summary>
	static inline float Det3x3(const FMatrix& m, int r0, int r1, int r2, int c0, int c1, int c2)
	{
		return m.M[r0][c0] * (m.M[r1][c1] * m.M[r2][c2] - m.M[r1][c2] * m.M[r2][c1])
			- m.M[r0][c1] * (m.M[r1][c0] * m.M[r2][c2] - m.M[r1][c2] * m.M[r2][c0])
			+ m.M[r0][c2] * (m.M[r1][c0] * m.M[r2][c1] - m.M[r1][c1] * m.M[r2][c0]);
	}

	/// <summary>
	/// 주어진 행(row)과 열(col)에 대한 Cofactor 계산
	/// </summary>
	static inline float Cofactor(const FMatrix& m, int row, int col)
	{
		// 4×4 행렬에서 지정한 row와 col을 제외한 3개의 행과 열을 선택합니다.
		int rows[3], cols[3];
		// row에 따른 rows 배열 할당
		if (row == 0)
		{
			rows[0] = 1;
			rows[1] = 2;
			rows[2] = 3;
		}
		else if (row == 1)
		{
			rows[0] = 0;
			rows[1] = 2;
			rows[2] = 3;
		}
		else if (row == 2)
		{
			rows[0] = 0;
			rows[1] = 1;
			rows[2] = 3;
		}
		else // row == 3
		{
			rows[0] = 0;
			rows[1] = 1;
			rows[2] = 2;
		}

		// col에 따른 cols 배열 할당
		if (col == 0)
		{
			cols[0] = 1;
			cols[1] = 2;
			cols[2] = 3;
		}
		else if (col == 1)
		{
			cols[0] = 0;
			cols[1] = 2;
			cols[2] = 3;
		}
		else if (col == 2)
		{
			cols[0] = 0;
			cols[1] = 1;
			cols[2] = 3;
		}
		else // col == 3
		{
			cols[0] = 0;
			cols[1] = 1;
			cols[2] = 2;
		}

		// 3×3 행렬식 계산
		float minor = Det3x3(m, rows[0], rows[1], rows[2], cols[0], cols[1], cols[2]);
		int sign = ((row + col) % 2 == 0) ? 1 : -1;
		return sign * minor;
	}

	/// <summary>
	/// <para>3D 변환행렬의 회전 행렬의 Adjoint(여인수)만 구해서 반환</para>
	/// 여인수는 Cofactor 행렬의 전치 행렬이다.
	/// </summary>
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

	/// <summary>
	/// 이 행렬(각 구성 요소는 행 벡터의 크기)에서 계산된 3D 스케일 벡터를 반환
	/// </summary>
	/// <returns></returns>
	FVector GetScaleVector() const;

	/// <summary>
	/// 이 행렬에서 스케일링을 제거(즉, 각 행의 크기가 1)
	/// </summary>
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

	/// <summary>
	/// scale이 제거된 행렬을 반환
	/// </summary>
	FMatrix GetMatrixWithOutScale() const;

	/// <summary>
	/// 이 행렬에서 이동 성분(Translation)을 제거
	/// </summary>
	/// <returns></returns>
	inline FMatrix RemoveTranslation() const
	{
		FMatrix result = *this;

		result.M[3][0] = 0.f;
		result.M[3][1] = 0.f;
		result.M[3][2] = 0.f;

		return result;
	}

	/// <summary>
	/// 이동 성분(Translation)을 추가한 행렬을 반환
	/// </summary>
	/// <param name="translation"></param>
	FMatrix AppendTranslation(const FVector& translation) const;

	/// <summary>
	/// 이 행렬에 scale을 적용한 행렬을 반환
	/// </summary>
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

	/// <summary>
	/// 행렬에 scale을 적용한 행렬을 반환
	/// </summary>
	/// <param name="scale"></param>
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

	/// <summary>
	/// x축을 기준으로 주어진 각도(angle)만큼 회전 행렬을 생성
	/// </summary>
	static FMatrix CreateRotationX(float angle);

	/// <summary>
	/// y축을 기준으로 주어진 각도(angle)만큼 회전 행렬을 생성
	/// </summary>
	static FMatrix CreateRotationY(float angle);

	/// <summary>
	/// z축을 기준으로 주어진 각도(angle)만큼 회전 행렬을 생성
	/// </summary>
	static FMatrix CreateRotationZ(float angle);

	/// <summary>
	/// rotation 벡터를 받아서 X, Y, Z 축을 기준으로 회전 행렬을 생성
	/// </summary>
	static FMatrix CreateRotationXYZ(const FVector& rotation);

	/// <summary>
	/// Quaternion을 받아서 회전 행렬을 생성
	/// </summary>
	static FMatrix CreateRotationQuat(const FQuaternion& q);

	/// <summary>
	/// Rotation 벡터를 받아서 X, Y, Z 축을 기준으로 회전
	/// </summary>
	inline void Rotate(const FVector& Rotation)
	{
		// 오일러 각도(도 단위) → 4×4 회전 행렬
		//FMatrix rotMat = CreateRotationXYZ(Rotation);

		// 쿼터니언 → 4×4 회전 행렬
		FMatrix rotMat = FMatrix::CreateRotationQuat(FQuaternion(Rotation));

		// 현재 행렬에 곱해 누적
		*this *= rotMat;
	}

	/// <summary>
	/// scale scalar 값을 받아서 X, Y, Z 축을 기준으로 스케일링 행렬을 생성
	/// </summary>
	static FMatrix CreateScaleMatrix(float scale);

	/// <summary>
	/// scale 벡터 값을 받아서 X, Y, Z 축을 기준으로 스케일링 행렬을 생성
	/// </summary>
	static FMatrix CreateScaleMatrix(const FVector& scale);

	/// <summary>
	/// 행렬의 이동(Translation) 부분을 지정된 벡터 값만큼 스케일링합니다.
	/// </summary>
	inline void ScaleTranslation(FVector& inScale3D)
	{
		M[3][0] *= inScale3D.X;
		M[3][1] *= inScale3D.Y;
		M[3][2] *= inScale3D.Z;
	}

	/// <summary>
	/// 행렬의 각 축(X, Y, Z)을 행렬이 가지고 있는 스케일(Scale)을 포함한 상태로 추출하여 반환
	/// </summary>
	inline void GetScaledAxes(FVector& outX, FVector& outY, FVector& outZ) const
	{
		outX.X = M[0][0]; outX = M[0][1]; outX.Z = M[0][2];
		outY.X = M[1][0]; outY.Y = M[1][1]; outY.Z = M[1][2];
		outZ.X = M[2][0]; outZ.Y = M[2][1]; outZ.Z = M[2][2];
	}

	/// <summary>
	/// 행렬의 축 방향만 가져오고, 크기(Scale)는 제외하여 반환
	/// </summary>
	inline void GetUnitAxes(FVector& outX, FVector& outY, FVector& outZ) const
	{
		GetScaledAxes(outX, outY, outZ);
		outX.GetNormalizedVector();
		outY.GetNormalizedVector();
		outZ.GetNormalizedVector();
	}

	/// <summary>
	/// <para>행렬의 특정 축(i번째 축)을 주어진 벡터로 설정</para>
	/// 행렬이 가지고 있는 X, Y, Z축 중에서 인자로 전달된 i에 해당하는 축을 axis라는 벡터 값으로 변경하는 함수
	/// </summary>
	inline void SetAxis(int i, const FVector& axis)
	{
		M[i][0] = axis.X;
		M[i][1] = axis.Y;
		M[i][2] = axis.Z;
	}

	/// <summary>
	/// 행렬의 X, Y, Z 축, 위치 성분을 각각 새 값으로 갱신
	/// </summary>
	inline void SetAxes(FVector& XAxis, FVector& YAxis, FVector& ZAxis, FVector& Origin)
	{
		SetAxis(0, XAxis);
		SetAxis(1, YAxis);
		SetAxis(2, ZAxis);
		SetOrigin(Origin);
	}

	/// <summary>
	/// <para>4×4 변환 행렬에서 위치(Translation) 성분만 추출</para>
	/// 해당 변환 행렬이 나타내는 좌표계의 위치(원점, Origin) 를 의미
	/// </summary>
	inline FVector GetOrigin() const
	{
		return FVector(M[3][0], M[3][1], M[3][2]);
	}

	/// <summary>
	/// <para>좌표계의 원점(위치)을 주어진 벡터로 설정</para>
	/// 변환 행렬의 위치(Translation) 성분을 특정 벡터값으로 설정하여, 해당 행렬이 표현하는 좌표계의 중심(원점)을 지정한 벡터 위치로 옮기는 함수
	/// </summary>
	inline void SetOrigin(const FVector& newOrigin)
	{
		M[3][0] = newOrigin.X;
		M[3][1] = newOrigin.Y;
		M[3][2] = newOrigin.Z;
	}

	/// <summary>
	/// <para>주어진 세 개의 축 벡터(X, Y, Z)와 원점 벡터를 사용하여 기저 행렬(새로운 좌표계(기저, Basis)를 나타내는 4×4 행렬)을 생성.</para>
	/// 좌표계에서 정의된 점(벡터)을 월드(또는 상위) 좌표계로 변환할 수 있음
	/// </summary>
	static FMatrix CreateBasisMatrix(const FVector& xAxis, const FVector& yAxis, const FVector& zAxis, const FVector& origin);

	/// <summary>
	/// location을 이용하여 이동 행렬을 생성
	/// </summary>
	static FMatrix CreateTranslationMatrix(const FVector& location);

	/// <summary>
	/// 행렬의 특정 Column(i번째 Column)을 반환
	/// </summary>
	inline FVector GetColumn(int i) const
	{
		return FVector(M[0][i], M[1][i], M[2][i]);
	}
	
	/// <summary>
	/// 행렬의 특정 Column(i번째 Column)을 주어진 벡터로 설정
	///	</summary>
	inline void SetColumn(int i, const FVector& v)
	{
		M[0][i] = v.X;
		M[1][i] = v.Y;
		M[2][i] = v.Z;
	}

	/// <summary>
	/// 행렬의 특정 Row(i번째 Row)을 반환
	/// </summary>
	inline FVector GetRow(int i) const
	{
		return FVector(M[i][0], M[i][1], M[i][2]);
	}

	/// <summary>
	/// 행렬의 특정 Row(i번째 Row)을 주어진 벡터로 설정
	/// </summary>
	inline void SetRow(int i, const FVector& v)
	{
		M[i][0] = v.X;
		M[i][1] = v.Y;
		M[i][2] = v.Z;
	}

	inline FVector GetForwardVector() const
	{
		// row 2가 X축
		return GetRow(2).GetNormalizedVector();
	}

	inline FVector GetRightVector() const
	{
		// row 1가 Y축
		return GetRow(1).GetNormalizedVector();
	}

	inline FVector GetUpVector() const
	{
		// row 0가 Z축
		return GetRow(0).GetNormalizedVector();
	}

	/// <summary>
	/// 왼손 좌표계(Left-Handed)에서 뷰 행렬을 생성
	/// </summary>
	/// <param name="eye">카메라 위치</param>
	/// <param name="toDir">카메라가 바라보는 방향 벡터</param>
	/// <param name="up">카메라의 upVector</param>
	static FMatrix CreateLookToMatrixLeftHand(const FVector& eye, const FVector& toDir, const FVector& up);

	/// <summary>
	/// 오른손 좌표계(Right-Handed)에서 뷰 행렬을 생성
	/// </summary>
	/// <param name="eye">카메라 위치</param>
	/// <param name="toDir">카메라가 바라보는 방향 벡터</param>
	/// <param name="up">카메라의 upVector</param>
	static FMatrix CreateLookToMatrixRightHand(const FVector& eye, const FVector& toDir, const FVector& up);

	/// <summary>
	/// 왼손 좌표계(Left-Handed)에서 Orthographic Projection(직각 투영) 행렬을 생성
	/// </summary>
	/// <returns></returns>
	static FMatrix CreateOrthographicProjectionMatrixLeftHand(float screenWidth, float screenHeight, float zNear, float zFar);

	/// <summary>
	/// 오른손 좌표계(Right-Handed)에서 Orthographic Projection(직각 투영) 행렬을 생성
	/// </summary>
	/// <returns></returns>
	static FMatrix CreateOrthographicProjectionMatrixRightHand(float screenWidth, float screenHeight, float zNear, float zFar);

	/// <summary>
	/// 왼손 좌표계(Left-Handed)에서 Perspective Projection(원근 투영) 행렬을 생성
	/// </summary>
	static FMatrix CreatePerspectiveProjectionMatrixLeftHand(float fov, float aspectRatio, float zNear, float zFar);
	/// <summary>
	/// 오른손 좌표계(Right-Handed)에서 Perspective Projection(원근 투영) 행렬을 생성
	/// </summary>
	static FMatrix CreatePerspectiveProjectionMatrixRightHand(float fov, float aspectRatio, float zNear, float zFar);
};
