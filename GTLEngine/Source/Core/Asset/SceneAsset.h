//#pragma once
//#include "Asset.h"
//
//struct Primitive
//{
//	Primitive(TArray<float> InLocation, TArray<float> InRotation, TArray<float> InScale, std::wstring InType)
//		: Location(InLocation), Rotation(InRotation), Scale(InScale), Type(InType)
//	{
//	}
//
//	Primitive()
//	{
//	}
//
//	Primitive(const Primitive& Other)
//	{
//		Location = Other.Location;
//		Rotation = Other.Rotation;
//		Scale = Other.Scale;
//		Type = Other.Type;
//	}
//
//	// 3D 좌표 정보: 위치, 회전, 스케일
//	TArray<float> Location;
//	TArray<float> Rotation;
//	TArray<float> Scale;
//	// 프리미티브 타입 (예: "Sphere", "Cube", "Triangle")
//	std::wstring Type;
//};
//
//struct FSceneData
//{
//	FSceneData(uint64 InVersion, uint64 InNextUUID, TMap<std::wstring, Primitive> InPrimitives)
//		: Version(InVersion), NextUUID(InNextUUID), Primitives(InPrimitives)
//	{
//	}
//
//	FSceneData()
//		: Version(0), NextUUID(0)
//	{
//	}
//
//	uint64 Version;
//	uint64 NextUUID;
//	TMap<std::wstring, Primitive> Primitives;
//};
//
//class USceneAsset : public UAsset
//{
//public:
//	
//public:
//	USceneAsset(FAssetMetaData metaData);
//	~USceneAsset();
//
//	bool RegistryAsset(FAssetMetaData metaData) override;
//	bool Load() override;
//	bool Save(std::wstring path = TEXT("")) override;
//	void Unload() override;
//
//	FSceneData GetSceneData() const { return SceneData; }
//
//private:
//	std::wstring StringToWString(const std::string& str);
//
//	std::string WStringToString(const std::wstring& wstr);
//private:
//	FSceneData SceneData;
//};
//
