#include "pch.h"
#include "Asset.h"
#include <iostream>
#include <filesystem>

using namespace std;

UAsset::UAsset()
	: bLoaded(false), AssetSize(0)
{

}

UAsset::~UAsset()
{
}

void UAsset::Tick(float TickTime)
{
}

void UAsset::Destroy()
{
}

bool UAsset::RegistryAsset(const std::wstring& name, const std::wstring& extention, const std::wstring& path)
{
	AssetName = name;
	AssetPath = path;
	AssetType = extention;

	return true;
}

