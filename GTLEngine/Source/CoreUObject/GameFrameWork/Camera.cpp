#include "pch.h"
#include "Camera.h"

#include "Components/CameraComponent.h"
#include "Engine/Engine.h"
#include "Input/InputManager.h"
#include "DirectXMath.h"
#include "World.h"
#include <Components/PrimitiveComponent.h>
#include "Resource/ResourceManager.h"

using namespace DirectX;

ACamera::ACamera()
{
	CameraComponent = AddComponent<UCameraComponent>(this);
	CameraComponent->SetupAttachment(RootComponent);
	SetActorLocation(FVector(0, 0, 0));
	SetActorRotation(FVector(0, 0, 0));
	SetActorScale(FVector(1, 1, 1));
}

void ACamera::Tick(float TickTime)
{
	FVector CameraLocation = GetActorLocation();
	FVector CameraRotation = GetActorRotation();

	UEngine& engine = UEngine::GetEngine();

	if (engine.GetInputManager()->GetKey('W'))
	{
		CameraLocation += FVector(0, 0, 10) * TickTime;
	}
	if (engine.GetInputManager()->GetKey('S'))
	{
		CameraLocation += FVector(0, 0, -10) * TickTime;
	}
	if (engine.GetInputManager()->GetKey('A'))
	{
		CameraLocation += FVector(-10, 0, 0) * TickTime;
	}
	if (engine.GetInputManager()->GetKey('D'))
	{
		CameraLocation += FVector(10, 0, 0) * TickTime;
	}
	if (engine.GetInputManager()->GetKey('Q'))
	{
		CameraLocation += FVector(0, -10, 0) * TickTime;
	}
	if (engine.GetInputManager()->GetKey('E'))
	{
		CameraLocation += FVector(0, 10, 0) * TickTime;
	}

	if (engine.GetInputManager()->GetMouseButton(UInputManager::EMouseButton::RIGHT))
	{
		float MouseDeltaX = engine.GetInputManager()->GetMouseDeltaX();
		float MouseDeltaY = engine.GetInputManager()->GetMouseDeltaY();

		CameraRotation += FVector(-MouseDeltaY, -MouseDeltaX , 0) * TickTime;
	}

	if (engine.GetInputManager()->GetMouseButton(UInputManager::EMouseButton::LEFT))
	{
		RayCasting();
	}

	SetActorLocation(CameraLocation);
	SetActorRotation(CameraRotation);
}

void ACamera::Destroy()
{
}

FMatrix ACamera::GetViewMatrix() const
{
	const FVector CameraLocation = GetActorLocation();
	const FVector CameraRotation = GetActorRotation();
	FMatrix rotationMatrix = FMath::CreateRotationMatrix(CameraRotation);
	FVector CameraDir = FMath::TransformDirection(FVector::RightVector, rotationMatrix);
	FVector CameraUp = FMath::TransformDirection(FVector::UpVector, rotationMatrix);

	return FMath::CreateViewMatrixByDirection(CameraLocation, CameraDir, CameraUp);
}

FMatrix ACamera::GetProjectionMatrix(float width, float height) const
{
	const float AspectRatio = width / height;

	return FMatrix::CreatePerspectiveProjectionMatrixLeftHand(60.f, AspectRatio, 1.f, 1000.f);
}

void ACamera::RayCasting()
{
	UEngine& engine = UEngine::GetEngine();

	float mouseNDCX = engine.GetInputManager()->GetMouseNdcX();
	float mouseNDCY = engine.GetInputManager()->GetMouseNdcY();

	float width = engine.GetWindowInfo().Width;
	float height = engine.GetWindowInfo().Height;

	FRay ray = FMath::CreateRay(GetViewMatrix(), GetProjectionMatrix(width, height), mouseNDCX, mouseNDCY, width, height);

	UWorld* world = UEngine::GetEngine().GetWorld();

	for (AActor* actor : world->GetActors())
	{
		UPrimitiveComponent* primitive = actor->GetComponentByClass<UPrimitiveComponent>();

		if (primitive != nullptr)
		{
			FMatrix primWorldMat = FMath::CreateWorldMatrix(actor->GetActorLocation(), actor->GetActorRotation(), actor->GetActorScale());
			FMatrix invPrimWorldMat;
			if (FMatrix::Inverse(primWorldMat, invPrimWorldMat))
			{
				float outW;
				FVector localOrigin = FMath::TransformPosition(ray.GetOrigin(), invPrimWorldMat, outW);
				localOrigin /= outW;
				FVector localDir = FMath::TransformDirection(ray.GetDirection(), invPrimWorldMat);

				FRay localRay = FRay(localOrigin, localDir);

				switch (primitive->GetPrimitiveType())
				{
					// ray를 각 물체의 좌표계로 변환하여 RayCasting
					case EPrimitiveType::Cone:
					{
						TArray<FVertexSimple> vertexData = UEngine::GetEngine().GetResourceManager()->GetVertexData(EPrimitiveType::Cone);
						TArray<FVector> vertexPos;
						for (auto& vertex : vertexData)
						{
							vertexPos.push_back(FVector(vertex.X, vertex.Y, vertex.Z));
						}
						FVector min, max;
						FMath::CaclulateAABB(vertexPos, min, max);
						float outT;
						if (FRayCast::IntersectRayAABB(localRay, min, max, outT))
						{
							FVector hitPos = localRay.GetOrigin() + localRay.GetDirection() * outT;
							FVector hitPosWorld = FMath::TransformPosition(hitPos, primWorldMat, outW);
							hitPosWorld /= outW;
						}
						break;
					}
					case EPrimitiveType::Cube:
					{
						TArray<FVertexSimple> vertexData = UEngine::GetEngine().GetResourceManager()->GetVertexData(EPrimitiveType::Cube);
						TArray<FVector> vertexPos;
						for (auto& vertex : vertexData)
						{
							vertexPos.push_back(FVector(vertex.X, vertex.Y, vertex.Z));
						}
						FVector min, max;
						FMath::CaclulateAABB(vertexPos, min, max);

						float outT;
						if (FRayCast::IntersectRayAABB(localRay, min, max, outT))
						{
							FVector hitPos = localRay.GetOrigin() + localRay.GetDirection() * outT;
							FVector hitPosWorld = FMath::TransformPosition(hitPos, primWorldMat, outW);
							hitPosWorld /= outW;
						}
						break;
					}
					case EPrimitiveType::Cylinder:
					{
						TArray<FVertexSimple> vertexData = UEngine::GetEngine().GetResourceManager()->GetVertexData(EPrimitiveType::Cylinder);
						TArray<FVector> vertexPos;
						for (auto& vertex : vertexData)
						{
							vertexPos.push_back(FVector(vertex.X, vertex.Y, vertex.Z));
						}
						FVector min, max;
						FMath::CaclulateAABB(vertexPos, min, max);

						float outT;
						if (FRayCast::IntersectRayAABB(localRay, min, max, outT))
						{
							FVector hitPos = localRay.GetOrigin() + localRay.GetDirection() * outT;
							FVector hitPosWorld = FMath::TransformPosition(hitPos, primWorldMat, outW);
							hitPosWorld /= outW;
						}
						break;
					}
					case EPrimitiveType::Plane:
					{
						TArray<FVertexSimple> vertexData = UEngine::GetEngine().GetResourceManager()->GetVertexData(EPrimitiveType::Plane);
						FVector v0 = FVector(vertexData[0].X, vertexData[0].Y, vertexData[0].Z);
						FVector v1 = FVector(vertexData[1].X, vertexData[1].Y, vertexData[1].Z);
						FVector v2 = FVector(vertexData[2].X, vertexData[2].Y, vertexData[2].Z);

						float outT;;
						if (FRayCast::IntersectRayTrianglePlane(localRay, v0, v1, v2, outT))
						{
							FVector hitPos = localRay.GetOrigin() + localRay.GetDirection() * outT;
							FVector hitPosWorld = FMath::TransformPosition(hitPos, primWorldMat, outW);
							hitPosWorld /= outW;
						}
						break;
					}
					case EPrimitiveType::Sphere:
					{
						TArray<FVertexSimple> vertexData = UEngine::GetEngine().GetResourceManager()->GetVertexData(EPrimitiveType::Sphere);

						float outT;
						if (FRayCast::InserSectRaySphere(localRay, FVector(0, 0, 0), 0.5f, outT))
						{
							FVector hitPos = localRay.GetOrigin() + localRay.GetDirection() * outT;
							FVector hitPosWorld = FMath::TransformPosition(hitPos, primWorldMat, outW);
							hitPosWorld /= outW;
						}
						break;
					}
					case EPrimitiveType::Line:
					{
						TArray<FVertexSimple> vertexData = UEngine::GetEngine().GetResourceManager()->GetVertexData(EPrimitiveType::Cylinder);

						break;
					}
					default:
					{
						break;
					}
				}
			}
		}
	}
}
