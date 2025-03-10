#pragma once
#include "Asset.h"
#include <iostream>

class UAssetManager
{
public:
	UAssetManager();
	~UAssetManager();

	/// <summary>
	/// 에디터 실행시 Contents 폴더에 있는 모든 에셋 메타데이터를 등록
	/// </summary>
	void RegistryAssetMetaDatas();

	/// <summary>
	/// 해당 에셋 메타데이터를 등록
	/// </summary>
	void RegistryAssetMetaData(const std::wstring& name, const std::wstring& path, uint64 fileSize, const std::wstring& extention);

	/// <summary>
	/// 메모리에 로드된 에셋을 찾아 반환 없으면 nullptr 반환
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="name"></param>
	/// <returns></returns>
	template <typename T>
	T* FindAsset(FAssetMetaData metaData)
	{
		auto iter = Assets.find(metaData.AssetName);
		if (iter == Assets.end())
		{
			return nullptr;
		}

		return dynamic_cast<T*>(iter->second);
	}

	/// <summary>
	/// 들고 있는 모든 메타 데이터들을 가지고 에셋을 로드
	/// </summary>
	void LoadAssets();

	/// <summary>
	/// <para>이름과 경로를 가지고 에셋을 로드</para>
	/// 각 에셋은 이름으로 관리되며 중복 로드는 방지 및	메모리 절약을 위해 이미 로드된 에셋은 반환
	/// </summary>
	template <typename T = UAsset>
	T* LoadAsset(FAssetMetaData metaData)
	{
		T* asset = FindAsset<T>(metaData);

		if (asset != nullptr)
		{
			return asset;
		}

		asset = new T(metaData);
		if (asset->Load() == false)
		{
			std::wcout << "Failed to load asset: " << metaData.AssetPath << std::endl;
			return nullptr;
		}

		return asset;
	}

	/// <summary>
	/// 들고 있는 모든 메타 데이터들을 가지고 에셋을 저장
	/// </summary>
	void SaveAssets();

	/// <summary>
	/// <para>이름과 경로를 가지고 에셋을 저장</para>
	/// 각 에셋은 이름으로 관리되며 이미 로드되어 있는 에셋은 메모리에 있는 데이터를 저장, 없으면 새로 생성하여 저장
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="name"></param>
	/// <param name="path"></param>
	template <typename T = UAsset>
	void SaveAsset(const std::wstring& name, const std::wstring& path)
	{
		T* asset = FindAsset<T>(name);
		if (asset == nullptr)
		{
			std::wcout << "New Asset : " << name << std::endl;
			
			FAssetMetaData metaData = FAssetMetaData(name, path);
			asset = new T(metaData);
			if(asset->Save(path) == false)
			{
				std::wcout << "Failed to save asset: " << path << std::endl;
				return;
			}
		}

		if (asset->Save() == false)
		{
			std::wcout << "Failed to save asset: " << path << std::endl;
			return;
		}

		return;
	}

	/// <summary>
	/// 모든 에셋을 메모리에서 해제
	/// </summary>
	void Release();
private:
	TMap<std::wstring, FAssetMetaData> AssetMetaDatas;
	TMap<std::wstring, UAsset*> Assets;
};
