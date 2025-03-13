#pragma once

struct FVector4;
struct FVector;
struct FRotator;
struct FQuat;

struct alignas(16) FMatrix
{
	float M[4][4];

	FMatrix();
	FMatrix(const FVector4& InX, const FVector4& InY, const FVector4& InZ, const FVector4& InW);
	FMatrix(const FRotator& Rotation);

	static FMatrix Identity(); // 단위행렬.
	static FMatrix Transpose(const FMatrix& Matrix); // 전치행렬.
	static FMatrix GetTranslateMatrix(float X, float Y, float Z); // 이동행렬.
	static FMatrix GetTranslateMatrix(FVector Translation); // 이동행렬.
	static FMatrix GetScaleMatrix(float X, float Y, float Z); // 스케일링 행렬.
	static FMatrix GetScaleMatrix(const FVector& InScale); // 스케일링 행렬.
	static FMatrix GetRotateMatrix(const FQuat& Q); // 회전행렬.
	static FMatrix LookAtLH(const FVector& EyePosition, const FVector& FocusPoint, const FVector& WorldUp); // 뷰 변환 행렬.
	static FMatrix PerspectiveFovLH(float FieldOfView, float AspectRatio, float NearPlane, float FarPlane); // 투영 행렬.

	FMatrix operator+(const FMatrix& Other) const;
	FMatrix operator+=(const FMatrix& Other);
	FMatrix operator-(const FMatrix& Other) const;
	FMatrix operator-=(const FMatrix& Other);
	FMatrix operator*(const FMatrix& Other) const;
	FMatrix operator*=(const FMatrix& Other);
	FMatrix operator*(float Other) const;
	FMatrix operator*=(float Other);
	bool operator==(const FMatrix& Other) const;
	bool operator!=(const FMatrix& Other) const;

	FMatrix GetTransposed() const; // 전치행렬.
	float Determinant() const; // 행렬식.
	FMatrix Inverse() const; // 역행렬.

	FVector GetTranslation() const; // 이동 벡터.
	FVector GetScale() const; // 스케일 벡터.
	FVector GetRotation() const; // 회전 벡터.
	FVector TransformVector(const FVector& Vector) const; // 3차원 벡터 변환.

	FVector4 TransformVector4(const FVector4& Vector) const; // 4차원 벡터 변환.

	class FTransform GetTransform() const; // 변환 행렬을 FTransform으로 변환.
};