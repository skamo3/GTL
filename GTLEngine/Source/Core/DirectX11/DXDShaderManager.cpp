#include "pch.h"
#include "DXDShaderManager.h"
#include "GTLStringLibrary.h"

#include "Engine/Engine.h"

UDXDShaderManager::UDXDShaderManager(ComPtr<ID3D11Device> Device)
	: DXDDevice(Device)
{
	VertexShaders.clear();
	PixelShaders.clear();
}

void UDXDShaderManager::ReleaseAllShader()
{
	for (auto Shader : VertexShaders)
	{
		if (Shader.second)
			Shader.second.Reset();
	}

	for (auto Shader : PixelShaders)
	{
		if (Shader.second)
			Shader.second.Reset();
	}

	PixelShaders.clear();
	if (PixelShaderCSO)
	{
		PixelShaderCSO.Reset();
	}
}

HRESULT UDXDShaderManager::AddPixelShader(const string& Name, const string& FileName)
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

	PixelShaders.insert(make_pair(Name, NewPixelShader));

	return S_OK;
}

HRESULT UDXDShaderManager::AddVertexShaderandInputLayout(const string& Name, const string& FilePath, const D3D11_INPUT_ELEMENT_DESC* Layout, uint LayoutSize)
{
	if (DXDDevice == nullptr)
		return S_FALSE;
	HRESULT hr;

	ComPtr<ID3DBlob> VertexShaderCSO;

	hr = D3DCompileFromFile(UGTLStringLibrary::StringToWString(FilePath).c_str(), nullptr, nullptr, "mainVS", "vs_5_0", 0, 0, &VertexShaderCSO, nullptr);
	if (FAILED(hr))
		return hr;

	ComPtr<ID3D11VertexShader> NewVertexShader;
	hr = DXDDevice->CreateVertexShader(VertexShaderCSO->GetBufferPointer(), VertexShaderCSO->GetBufferSize(), nullptr, &NewVertexShader);
	if (FAILED(hr))
		return hr;
	VertexShaders.insert(make_pair(Name, NewVertexShader));

	ComPtr<ID3D11InputLayout> NewInputLayout;
	hr = DXDDevice->CreateInputLayout(Layout, LayoutSize, VertexShaderCSO->GetBufferPointer(), VertexShaderCSO->GetBufferSize(), &NewInputLayout);
	if (FAILED(hr))
		return hr;

	InputLayouts.insert(make_pair(Name, NewInputLayout));
	

	return S_OK;
}

ComPtr<ID3D11VertexShader> UDXDShaderManager::GetVertexShaderByKey(const string& Name) const
{
	if (VertexShaders.find(Name) == VertexShaders.end())
		return nullptr;
	return VertexShaders.at(Name);
}

ComPtr<ID3D11PixelShader> UDXDShaderManager::GetPixelShaderByKey(const string& Name) const
{
	if (PixelShaders.find(Name) == PixelShaders.end())
		return nullptr;
	return PixelShaders.at(Name);
}
