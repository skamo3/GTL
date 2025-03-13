﻿#pragma once
#include "Matrix.h"
#include "Ray.h"

struct FMath
{
	inline static float RadToDeg(float radian)
	{
		return radian * (180.0f / PI);
	}

	inline static float DegToRad(float degree)
	{
		return degree * (PI / 180.0f);
	}

	/// <summary>
	/// scale 값을 사용하여 스케일링 행렬을 생성
	/// </summary>
	static FMatrix CreateScaleMatrix(float scale);

	/// <summary>
	/// scale 벡터를 사용하여 스케일링 행렬을 생성
	/// </summary>
	static FMatrix CreateScaleMatrix(const FVector& scale);

	/// <summary>
	/// roll(X), yaw(Y), pitch(Z) 각도를 사용하여 회전 행렬을 생성
	/// </summary>
	static FMatrix CreateRotationMatrix(float roll, float yaw, float pitch);

	/// <summary>
	/// rotation 벡터를 사용하여 회전 행렬을 생성
	/// </summary>
	static FMatrix CreateRotationMatrix(const FVector& rotation);

	static FMatrix CreateRotationMatrix(const FQuaternion& quaternion);

	/// <summary>
	/// Location 벡터를 사용하여 이동 행렬을 생성
	/// </summary>
	static FMatrix CreateTranslationMatrix(const FVector& location);


	/// <summary>
	/// X, Y, Z 값을 사용하여 이동 행렬을 생성
	/// </summary>
	static FMatrix CreateTranslationMatrix(float x, float y, float z);


	/// <summary>
	/// position, rotation, scale 벡터를 사용하여 World 행렬을 생성
	/// </summary>
	static FMatrix CreateWorldMatrix(const FVector& position, const FVector& rotation, const FVector& scale);

	/// <summary>
	/// <para>주어진 세 개의 축 벡터(X, Y, Z)와 원점 벡터를 사용하여 기저 행렬(새로운 좌표계(기저, Basis)를 나타내는 4×4 행렬)을 생성.</para>
	/// 좌표계에서 정의된 점(벡터)을 월드(또는 상위) 좌표계로 변환할 수 있음
	/// </summary>
	static FMatrix CreateBasisMatrix(const FVector& xAxis, const FVector& yAxis, const FVector& zAxis, const FVector& origin);

	/// <summary>
	/// View 행렬을 생성
	/// </summary>
	/// <param name="eye">카메라 위치</param>
	/// <param name="target">카메라가 바라보는 위치 벡터</param>
	/// <param name="up">카메라 기준 upVector</param>
	/// <param name="isLeft">왼손 좌표계면 true, 오른손 좌표계면 false</param>
	//static FMatrix CreateViewMatrixByTargetPos(const FVector& eye, const FVector& target, const FVector& up, bool isLeft = true);

	/// <summary>
	/// View 행렬을 생성
	/// </summary>
	/// <param name="eye">카메라 위치</param>
	/// <param name="direction">카메라가 바라보는 방향 벡터</param>
	/// <param name="up">카메라 기준 upVector</param>
	/// <param name="isLeft">왼손 좌표계면 true, 오른손 좌표계면 false</param>
	static FMatrix CreateViewMatrixByDirection(const FVector& eye, const FVector& direction, const FVector& up, bool isLeft = true);

	/// <summary>
	/// Orthographic Projection(직각 투영) 행렬을 생성
	/// </summary>
	/// <param name="screenWidth">화면 넓이</param>
	/// <param name="screenHeight">화면 높이</param>
	/// <param name="zNear">ViewFrustum Near</param>
	/// <param name="zFar">ViewFrustum Far</param>
	/// <param name="isLeft">왼손 좌표계면 true, 오른손 좌표계면 false</param>
	/// <returns></returns>
	static FMatrix CreateOrthographicProjectionMatrix(float screenWidth, float screenHeight, float zNear, float zFar, bool isLeft = true);

	/// <summary>
	/// Perspective Projection(원근 투영) 행렬을 생성
	/// </summary>
	/// <param name="fov">Fov 각도</param>
	/// <param name="width">화면 넓이</param>
	/// <param name="height">화면 높이</param>
	/// <param name="zNear">ViewFrustum Near</param>
	/// <param name="zFar">ViewFrustum Far</param>
	/// <param name="isLeft">왼손 좌표계면 true, 오른손 좌표계면 false</param>
	/// <returns></returns>
	static FMatrix CreatePerspectiveProjectionMatrix(float fov, float width, float height, float zNear, float zFar, bool isLeft = true);

	/// <summary>
	/// Perspective Projection(원근 투영) 행렬을 생성
	/// </summary>
	/// <param name="fov">Fov 각도</param>
	/// <param name="aspectRatio">화면 비율</param>
	/// <param name="zNear">ViewFrustum Near</param>
	/// <param name="zFar">ViewFrustum Far</param>
	/// <param name="isLeft">왼손 좌표계면 true, 오른손 좌표계면 false</param>
	/// <returns></returns>
	static FMatrix CreatePerspectiveProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar, bool isLeft = true);

	/// <summary>
	/// model->view->projection 행렬 변환하여 MVP 행렬을 생성
	/// </summary>
	static FMatrix CreateMVP(const FMatrix& modelMat, const FMatrix& viewMat, const FMatrix& projMat);

	/// <summary>
	/// (위치 벡터) x (행렬) = 변환된 위치 연산을 수행하고, 결과적인 새 위치 벡터(회전·스케일 반영, 평행이동 포함)를 반환
	/// </summary>
	static FVector TransformPosition(const FVector& pos, const FMatrix& m, float& outW);

	/// <summary>
	/// (법선·방향 벡터) × (행렬) = 변환된 방향 연산을 수행하고, 결과적인 새 방향 벡터(회전·스케일 반영, 평행이동 무시)를 반환
	/// </summary>
	static FVector TransformDirection(const FVector& dir, const FMatrix& m);

	/// <summary>
	/// Mouse Position을 사용하여 Ray를 생성
	/// </summary>
	static FRay CreateRay(const FMatrix& viewMatrix, const FMatrix& projMatrix, const FVector& mousePos, float screenWidth, float screenHeight);

	/// <summary>
	/// Mouse Position을 사용하여 Ray를 생성
	/// </summary>
	/// <param name="ndcMouseX">ndc 좌표로 변환된 MouseX</param>
	/// <param name="ndcMouseY">ndc 좌표로 변환된 MouseY</param>
	static FRay CreateRay(const FMatrix& viewMatrix, const FMatrix& projMatrix, float ndcMouseX, float ndcMouseY, float screenWidth, float screenHeight);

	static void CaclulateAABB(const TArray<FVector>& vertices, FVector& outMin, FVector& outMax);
};

