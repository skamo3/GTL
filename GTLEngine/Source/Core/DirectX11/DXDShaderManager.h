#pragma once

struct FVertexShader
{
	ComPtr<ID3D11VertexShader> VertexShader;
	ComPtr<ID3D11InputLayout> InputLayout;
};

class UDXDShaderManager
{
public:
	UDXDShaderManager() = default;
	UDXDShaderManager(ComPtr<ID3D11Device> Device);

	void ReleaseAllShader();

private:
	ComPtr<ID3D11Device> DXDDevice;

public:
	
	HRESULT AddVertexShaderAndInputLayout(const std::wstring& Key, const std::wstring& FileName, const D3D11_INPUT_ELEMENT_DESC* Layout, uint LayoutSize);

	HRESULT AddPixelShader(const std::wstring& Key, const std::wstring& FileName);

	ComPtr<ID3D11VertexShader> GetVertexShaderByKey(const std::wstring& Key) const;
	ComPtr<ID3D11PixelShader> GetPixelShaderByKey(const std::wstring& Key) const;

private:
	TMap<std::wstring, ComPtr<ID3D11InputLayout>> InputLayouts;
	TMap<std::wstring, ComPtr<ID3D11VertexShader>> VertexShaders;
	TMap<std::wstring, ComPtr<ID3D11PixelShader>> PixelShaders;

};

