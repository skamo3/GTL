#include "pch.h"
#include "Scene.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include "SimpleJSON/json.hpp"

using namespace std;

UScene::UScene()
{
}

UScene::~UScene()
{
}

bool UScene::RegistryAsset(const std::wstring& name, const std::wstring& extention, const std::wstring& path)
{
	if (UAsset::RegistryAsset(name, extention, path) == false)
		return  false;
	

	return true;
}

bool UScene::LoadAsset()
{
	if (bLoaded)
	{
		wcout << "Asset already loaded: " << AssetPath << endl;
		return true;
	}

	filesystem::path filePath = AssetPath;
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

	TMap<std::string, Primitive> loadedPrimitives;
	auto primitivesObj = primitives.ObjectRange();
	for (auto it = primitivesObj.begin(); it != primitivesObj.end(); ++it)
	{
		string key = it->first;
		json::JSON primitive = it->second;

		Primitive loadedPrimitive;
		loadedPrimitive.Type = primitive["Type"].ToString();

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

	SceneData = { version, nextUUID, loadedPrimitives };
	bLoaded = true;
}

bool UScene::SaveAsset()
{
	json::JSON sceneData = json::JSON::Make(json::JSON::Class::Object);

	sceneData["Version"] = SceneData.Version;
	sceneData["NextUUID"] = SceneData.NextUUID;

	json::JSON primitives = json::JSON::Make(json::JSON::Class::Object);
	for (const auto& primitive : SceneData.Primitives)
	{
		json::JSON primitiveData = json::JSON::Make(json::JSON::Class::Object);
		primitiveData["Type"] = primitive.second.Type;
	
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
	}

	sceneData["Primitives"] = primitives;


	string jsonStr = sceneData.dump(2);

	filesystem::path filePath = AssetPath;
	ofstream file(filePath);
	if (!file.is_open())
	{
		wcout << "File open failed: " << filePath << endl;
		return false;
	}

	file << jsonStr;
	file.close();

	return true;
}

void UScene::UnloadAsset()
{
	if (bLoaded)
	{
		// 메모리 해제
	}
}
