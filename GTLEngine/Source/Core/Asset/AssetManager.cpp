#include "pch.h"
#include "AssetManager.h"
#include <filesystem>
#include <iostream>
#include "SceneAsset.h"


using namespace std;

UAssetManager::UAssetManager()
{
}

UAssetManager::~UAssetManager()
{
}

void UAssetManager::RegistryAssetMetaDatas()
{
	if (IsDebuggerPresent())
	{
		filesystem::path curPath = filesystem::current_path();
		filesystem::path assetDir = curPath / L"Resources";
		try
		{
			for (const auto& entry : filesystem::recursive_directory_iterator(assetDir))
			{
				if (filesystem::is_regular_file(entry.status()))
				{
					filesystem::path filePath = entry.path();

					// 파일의 확장자, 전체 경로, 파일 크기를 가져옵니다.
					wstring fileName = filePath.stem().wstring();
					wstring extension = filePath.extension().wstring();
					wstring fullPath = filePath.wstring();
					uint64 fileSize = filesystem::file_size(filePath);

					RegistryAssetMetaData(fileName, fullPath, fileSize, extension);
				}
			}
		}
		catch (std::filesystem::filesystem_error& e)
		{
			std::wcout << e.what() << std::endl;
		}
	}
	else
	{
		// 빌드된 실행 파일의 경로로 설정
	}
}

void UAssetManager::RegistryAssetMetaData(const std::wstring& fileName, const std::wstring& fullPath, uint64 fileSize, const std::wstring& extention)
{
	if (AssetMetaDatas.find(fileName) == AssetMetaDatas.end())
	{
		AssetMetaDatas[fileName] = FAssetMetaData(fileName, fullPath, fileSize, extention);
	}
}

void UAssetManager::LoadAssets()
{
	for (auto& assetMetaData : AssetMetaDatas)
	{
		switch (assetMetaData.second.AssetType)
		{
			case EAssetType::Texture:
			{
				//TODO : Texture Asset 로드
				break;
			}
			break;
			case EAssetType::Mesh:
			{
				//TODO : Mesh Asset 로드
				break;
			}
			case EAssetType::AudioClip:
			{
				//TODO : AudioClip Asset 로드
				break;
			}
			break;
			case EAssetType::SceneAsset:
			{
				USceneAsset* sceneAsset = LoadAsset<USceneAsset>(assetMetaData.second);
				break;
			}
		}
	}
}

void UAssetManager::SaveAssets()
{
	for (auto& asset : Assets)
	{
		asset.second->Save();
	}
}

void UAssetManager::Release()
{
	AssetMetaDatas.clear();

	for (auto& item : Assets)
	{
		item.second->Destroy();
		delete item.second;
	}
	Assets.clear();
}
