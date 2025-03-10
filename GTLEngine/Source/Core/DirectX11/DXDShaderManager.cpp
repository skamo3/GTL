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
    for (auto& [Key, Shader] : VertexShaders)
    {
        if (Shader)
        {
            Shader.Reset();
        }
    }
    VertexShaders.clear();

    for (auto& [Key, Shader] : PixelShaders)
    {
        if (Shader)
        {
            Shader.Reset();
        }
    }
    PixelShaders.clear();

    DXDDevice.Reset();
}

HRESULT UDXDShaderManager::AddPixelShader(const std::wstring& Key, const std::wstring& FileName)
{
    HRESULT hr = S_OK;

    if (DXDDevice == nullptr)
        return S_FALSE;

    ID3DBlob* PsBlob = nullptr;
    hr = D3DCompileFromFile(FileName.c_str(), nullptr, nullptr, "mainPS", "ps_5_0", 0, 0, &PsBlob, nullptr);
    if (FAILED(hr))
        return hr;

    ComPtr<ID3D11PixelShader> NewPixelShader;
    hr = DXDDevice->CreatePixelShader(PsBlob->GetBufferPointer(), PsBlob->GetBufferSize(), nullptr, &NewPixelShader);
    if (PsBlob)
    {
        PsBlob->Release();
    }
    if (FAILED(hr))
        return hr;

    PixelShaders[Key] = NewPixelShader;

    return S_OK;
}

HRESULT UDXDShaderManager::AddVertexShaderAndInputLayout(const std::wstring& Key, const std::wstring& FilePath, const D3D11_INPUT_ELEMENT_DESC* Layout, uint LayoutSize)
{
    if (DXDDevice == nullptr)
        return S_FALSE;

    HRESULT hr = S_OK;

    ComPtr<ID3DBlob> VertexShaderCSO = nullptr;

    hr = D3DCompileFromFile(FilePath.c_str(), nullptr, nullptr, "mainVS", "vs_5_0", 0, 0, &VertexShaderCSO, nullptr);
    if (FAILED(hr))
        return hr;

    ComPtr<ID3D11VertexShader> NewVertexShader;
    hr = DXDDevice->CreateVertexShader(VertexShaderCSO->GetBufferPointer(), VertexShaderCSO->GetBufferSize(), nullptr, &NewVertexShader);
    if (FAILED(hr))
    {
        if (VertexShaderCSO)
        {
            VertexShaderCSO->Release();
        }
        return hr;
    }

    ComPtr<ID3D11InputLayout> NewInputLayout;
    hr = DXDDevice->CreateInputLayout(Layout, LayoutSize, VertexShaderCSO->GetBufferPointer(), VertexShaderCSO->GetBufferSize(), &NewInputLayout);
    if (FAILED(hr))
    {
        if (VertexShaderCSO)
        {
            VertexShaderCSO->Release();
        }
        return hr;
    }

    VertexShaders.insert(make_pair(Key, NewVertexShader));
    InputLayouts.insert(make_pair(Key, NewInputLayout));
    
    return S_OK;
}

ComPtr<ID3D11VertexShader> UDXDShaderManager::GetVertexShaderByKey(const std::wstring& Key) const
{
    if (VertexShaders.contains(Key))
    {
        return VertexShaders.at(Key);
    }
    return nullptr;
}

ComPtr<ID3D11PixelShader> UDXDShaderManager::GetPixelShaderByKey(const std::wstring& Key) const
{
    if (PixelShaders.contains(Key))
    {
        return PixelShaders.at(Key);
    }
    return nullptr;
}
