#include "pch.h"
#include "SceneAsset.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include "SimpleJson/json.hpp"

using namespace std;

USceneAsset::USceneAsset(FAssetMetaData metaData)
	: UAsset(metaData), SceneData(FSceneData())
{
}

USceneAsset::~USceneAsset()
{
}

bool USceneAsset::RegistryAsset(FAssetMetaData metaData)
{
	if(UAsset::RegistryAsset(metaData) == false)
	{
		return false;
	}

	return true;
}

bool USceneAsset::Load()
{
	if (IsLoaded())
	{
		wcout << "Asset already loaded: " << AssetMetaData.AssetPath << endl;
		return true;
	}

	filesystem::path filePath = AssetMetaData.AssetPath;
	if (filesystem::exists(filePath) == false)
	{
		wcout << "File not found: " << filePath << endl;
		return false;
	}

	ifstream file(filePath);
	if (file.is_open() == false)
	{
		wcout << "File open failed: " << filePath << endl;
		return false;
	}

	ostringstream oss;
	oss << file.rdbuf();
	string jsonStr = oss.str();

	json::JSON sceneData = json::JSON::Load(jsonStr);

	uint64 version = sceneData["Version"].ToInt();
	uint64 nextUUID = sceneData["NextUUID"].ToInt();

	json::JSON primitives = sceneData["Primitives"];

	TMap<std::wstring, Primitive> loadedPrimitives;
	auto primitivesObj = primitives.ObjectRange();
	for (auto it = primitivesObj.begin(); it != primitivesObj.end(); ++it)
	{
		wstring key = StringToWString(it->first);
		json::JSON primitive = it->second;

		Primitive loadedPrimitive;
		loadedPrimitive.Type = StringToWString(primitive["Type"].ToString());

		auto locationArr = primitive["Location"].ArrayRange();
		for (const auto& location : locationArr)
		{
			float value = location.ToFloat();
			loadedPrimitive.Location.push_back(value);
		}

		auto rotationArr = primitive["Rotation"].ArrayRange();
		for (const auto& rotation : rotationArr)
		{
			float value = rotation.ToFloat();
			loadedPrimitive.Rotation.push_back(value);
		}

		auto scaleArr = primitive["Scale"].ArrayRange();
		for (const auto& scale : scaleArr)
		{
			float value = scale.ToFloat();
			loadedPrimitive.Scale.push_back(value);
		}

		loadedPrimitives[key] = loadedPrimitive;
	}

	SceneData = FSceneData(version, nextUUID, loadedPrimitives);

	AssetMetaData.bLoaded = true;
	return true;
}

bool USceneAsset::Save(std::wstring path)
{
	json::JSON sceneData = json::JSON::Make(json::JSON::Class::Object);

	sceneData["Version"] = SceneData.Version;
	sceneData["NextUUID"] = SceneData.NextUUID;

	json::JSON primitives = json::JSON::Make(json::JSON::Class::Object);
	for (const auto& primitive : SceneData.Primitives)
	{
		json::JSON primitiveData = json::JSON::Make(json::JSON::Class::Object);

		json::JSON location = json::JSON::Make(json::JSON::Class::Array);
		for (const auto& value : primitive.second.Location)
		{
			location.append(value);
		}
		primitiveData["Location"] = location;

		json::JSON rotation = json::JSON::Make(json::JSON::Class::Array);
		for (const auto& value : primitive.second.Rotation)
		{
			rotation.append(value);
		}
		primitiveData["Rotation"] = rotation;

		json::JSON scale = json::JSON::Make(json::JSON::Class::Array);
		for (const auto& value : primitive.second.Scale)
		{
			scale.append(value);
		}
		primitiveData["Scale"] = scale;

		primitives.append(primitive.first, primitiveData);


		primitiveData["Type"] = WStringToString(primitive.second.Type);
	}

	sceneData["Primitives"] = primitives;


	string jsonStr = sceneData.dump(2);

	if (path.empty())
	{
		path = AssetMetaData.AssetPath;
	}

	ofstream file(path);
	if (!file.is_open())
	{
		wcout << "File open failed: " << path << endl;
		return false;
	}

	file << jsonStr;
	file.close();

	return true;
}

void USceneAsset::Unload()
{
}

std::wstring USceneAsset::StringToWString(const std::string& str)
{
	// 필요한 버퍼 길이 계산 (널 문자 포함)
	int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
	if (len == 0)
		throw std::runtime_error("MultiByteToWideChar 에러");

	std::wstring wstr(len, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], len);
	// 마지막 널 문자를 제거할 수 있음
	if (!wstr.empty() && wstr.back() == L'\0')
		wstr.pop_back();
	return wstr;
}

std::string USceneAsset::WStringToString(const std::wstring& wstr)
{
	// UTF-8 문자열로 변환하기 위해 필요한 버퍼 길이 계산 (널 문자 포함)
	int len = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	if (len == 0)
		throw std::runtime_error("WideCharToMultiByte 에러");

	std::string str(len, '\0');
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], len, nullptr, nullptr);
	// 마지막 널 문자가 추가되어 있다면 제거
	if (!str.empty() && str.back() == '\0')
		str.pop_back();
	return str;
}
