#pragma once
#include "Object.h"

class UAsset : public UObject
{
public:
	UAsset();
	~UAsset();

	// UObject을(를) 통해 상속됨
	void Tick(float TickTime) override;
	void Destroy() override;

	// Asset 로드 및 언로드 인터페이스
	virtual bool RegistryAsset(const std::wstring& name, const std::wstring& extention, const std::wstring& path);
	virtual bool LoadAsset() = 0;
	virtual bool SaveAsset() = 0;
	virtual void UnloadAsset() = 0;
	bool IsLoaded() const { return bLoaded; }

	// Accessor: Asset 이름, 경로, 크기, 타입 등
	const std::wstring& GetAssetName() const { return AssetName; }
	const std::wstring& GetAssetPath() const { return AssetPath; }
	uint32_t GetAssetSize() const { return AssetSize; }
	const std::wstring& GetAssetType() const { return AssetType; }

/// <summary>
/// 메타 데이터들
/// </summary>
protected:
	std::wstring AssetName;

	std::wstring AssetPath;

	// 추가 멤버들
	bool bLoaded;              // Asset이 메모리에 로드되었는지 여부
	uint32_t AssetSize;        // Asset 파일 크기 (바이트 단위)
	std::wstring AssetType;    // 일단 확장자 타입 
};

