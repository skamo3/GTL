#pragma once
#include "Object.h"
#include <string>

enum class EAssetType
{
	Texture,
	Mesh,
	AudioClip,
	SceneAsset,
	End
};

struct FAssetMetaData
{
public:
	FAssetMetaData(std::wstring assetName, std::wstring assetPath, uint64 assetSize, std::wstring assetType)
		: AssetName(assetName), AssetPath(assetPath), AssetSize(assetSize), bLoaded(false)
	{
		if (assetType == L".png" || assetType == L".jpg" || assetType == L".bmp")
			AssetType = EAssetType::Texture;
		else if (assetType == L".fbx" || assetType == L".obj")
			AssetType = EAssetType::Mesh;
		else if (assetType == L".mp3" || assetType == L".wav")
			AssetType = EAssetType::AudioClip;
		else if (assetType == L".Scene")
			AssetType = EAssetType::SceneAsset;
		else
			AssetType = EAssetType::End;
	}

	FAssetMetaData(std::wstring assetName, std::wstring assetPath)
		: AssetName(assetName), AssetPath(assetPath), AssetSize(0), bLoaded(false), AssetType(EAssetType::End)
	{
	}

	FAssetMetaData()
		: AssetName(L""), AssetPath(L""), AssetSize(0), bLoaded(false), AssetType(EAssetType::End)
	{
	}


	std::wstring AssetName;
	std::wstring AssetPath;

	// 추가 멤버들
	bool bLoaded;              // Asset이 메모리에 로드되었는지 여부
	uint64 AssetSize;        // Asset 파일 크기 (바이트 단위)
	EAssetType AssetType;    // 일단 확장자 타입 
};

class UAsset : public UObject
{
public:
	UAsset(FAssetMetaData assetData);
	~UAsset();

	// UObject을(를) 통해 상속됨
	void Tick(float TickTime) override;
	void Destroy() override;

	// Asset 로드 및 언로드 인터페이스
	virtual bool RegistryAsset(FAssetMetaData metaData);
	virtual bool Load() = 0;
	virtual bool Save(std::wstring path = TEXT("")) = 0;
	virtual void Unload() = 0;

	inline bool IsLoaded() const { return AssetMetaData.bLoaded; }

	// Accessor: Asset 이름, 경로, 크기, 타입 등
	inline const std::wstring& GetAssetName() const { return AssetMetaData.AssetName; }
	inline const std::wstring& GetAssetPath() const { return AssetMetaData.AssetPath; }
	inline uint64 GetAssetSize() const { return AssetMetaData.AssetSize; }
	inline const EAssetType GetAssetType() const { return AssetMetaData.AssetType; }

/// <summary>
/// 메타 데이터들
/// </summary>
protected:
	FAssetMetaData AssetMetaData;
};

