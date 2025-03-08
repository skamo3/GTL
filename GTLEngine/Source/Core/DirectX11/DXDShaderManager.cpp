#include "pch.h"
#include "DXDShaderManager.h"
#include "GTLStringLibrary.h"

#include "Engine/Engine.h"

UDXDShaderManager::UDXDShaderManager(ComPtr<ID3D11Device> Device)
	: DXDDevice(Device)
{
	VertexShader.clear();
	PixelShader.clear();
}

void UDXDShaderManager::ReleaseAllShader()
{
	for (auto Shader : VertexShader)
	{
		if (Shader.second)
			Shader.second.Reset();
	}

	for (auto Shader : PixelShader)
	{
		if (Shader.second)
			Shader.second.Reset();
	}

	VertexShader.clear();
	PixelShader.clear();
	if (VertexShaderCSO)
	{
		VertexShaderCSO->Release();
		VertexShaderCSO.Reset();
	}
	if (PixelShaderCSO)
	{
		PixelShaderCSO->Release();
		PixelShaderCSO.Reset();
	}
}

HRESULT UDXDShaderManager::AddVertexShader(const string& FileName, ComPtr<ID3DBlob> Blob)
{
	HRESULT hr;

	if (DXDDevice == nullptr)
		return S_FALSE;

	hr = D3DCompileFromFile(UGTLStringLibrary::StringToWString(FileName).c_str(), nullptr, nullptr, "mainVS", "vs_5_0", 0, 0, &Blob, nullptr);
	if (FAILED(hr))
		return hr;

	ComPtr<ID3D11VertexShader> NewVertexShader;
	hr = DXDDevice->CreateVertexShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &NewVertexShader);
	if (FAILED(hr))
		return hr;
	VertexShader.insert(make_pair(FileName, NewVertexShader));

	return S_OK;
}

HRESULT UDXDShaderManager::AddPixelShader(const string& FileName)
{
	HRESULT hr;

	if (DXDDevice == nullptr)
		return S_FALSE;

	hr = D3DCompileFromFile(UGTLStringLibrary::StringToWString(FileName).c_str(), nullptr, nullptr, "mainPS", "ps_5_0", 0, 0, &PixelShaderCSO, nullptr);
	if (FAILED(hr))
		return hr;

	ComPtr<ID3D11PixelShader> NewPixelShader;
	hr = DXDDevice->CreatePixelShader(PixelShaderCSO->GetBufferPointer(), PixelShaderCSO->GetBufferSize(), nullptr, &NewPixelShader);
	if (FAILED(hr))
		return hr;

	PixelShader.insert(make_pair(FileName, NewPixelShader));

	return S_OK;
}

ComPtr<ID3D11VertexShader> UDXDShaderManager::GetVertexShaderByKey(const string& Name) const
{
	if (VertexShader.find(Name) == VertexShader.end())
		return nullptr;
	return VertexShader.at(Name);
}

ComPtr<ID3D11PixelShader> UDXDShaderManager::GetPixelShaderByKey(const string& Name) const
{
	if (PixelShader.find(Name) == PixelShader.end())
		return nullptr;
	return PixelShader.at(Name);
}
