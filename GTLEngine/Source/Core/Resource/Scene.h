#pragma once
#include "Core/Resource/Asset.h"

class UScene : public UAsset
{
public:
	struct Primitive
	{
		Primitive(TArray<float> InLocation, TArray<float> InRotation, TArray<float> InScale, std::string InType)
			: Location(InLocation), Rotation(InRotation), Scale(InScale), Type(InType)
		{
		}

		Primitive()
		{
			Location = { 0.f, 0.f, 0.f };
			Rotation = { 0.f, 0.f, 0.f };
			Scale = { 1.f, 1.f, 1.f };
			Type = "";
		}

		Primitive(const Primitive& Other)
		{
			Location = Other.Location;
			Rotation = Other.Rotation;
			Scale = Other.Scale;
			Type = Other.Type;
		}

		// 3D 좌표 정보: 위치, 회전, 스케일
		TArray<float> Location;
		TArray<float> Rotation;
		TArray<float> Scale;
		// 프리미티브 타입 (예: "Sphere", "Cube", "Triangle")
		std::string Type;
	};

	struct FSceneData
	{
		FSceneData(uint64 InVersion, uint64 InNextUUID, TMap<std::string, Primitive> InPrimitives)
			: Version(InVersion), NextUUID(InNextUUID), Primitives(InPrimitives)
		{
		}

		FSceneData()
			: Version(0), NextUUID(0)
		{
		}

		uint64 Version;
		uint64 NextUUID;
		TMap<std::string, Primitive> Primitives;
	};

	UScene();
	~UScene();

	bool RegistryAsset(const std::wstring& name, const std::wstring& extention, const std::wstring& path) override;
	bool LoadAsset() override;
	bool SaveAsset() override;
	void UnloadAsset() override;
private:
	FSceneData SceneData;
};

