#include "pch.h"
#include "Asset.h"
#include <iostream>
#include <filesystem>

using namespace std;

UAsset::UAsset(FAssetMetaData assetData)
	: UObject(), AssetMetaData(assetData)
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

bool UAsset::RegistryAsset(FAssetMetaData metaData)
{
	AssetMetaData = metaData;
	return true;
}


