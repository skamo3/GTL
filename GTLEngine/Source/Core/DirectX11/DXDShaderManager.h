#pragma once

struct FVertexShaderData
{
	ID3DBlob* VertexShaderCSO;
	ID3D11VertexShader* VertexShader;
};

class UDXDShaderManager
{
public:
	UDXDShaderManager() = default;
	UDXDShaderManager(ID3D11Device* Device);

	void ReleaseAllShader();

private:
	ID3D11Device* DXDDevice;

public:
	HRESULT AddVertexShader(const std::wstring& Key, const std::wstring& FileName);
	HRESULT AddInputLayout(const std::wstring& Key, const D3D11_INPUT_ELEMENT_DESC* Layout, uint LayoutSize);

	
	HRESULT AddVertexShaderAndInputLayout(const std::wstring& Key, const std::wstring& FileName, const std::string& EntryPoint, const D3D11_INPUT_ELEMENT_DESC* Layout, uint LayoutSize);

	HRESULT AddPixelShader(const std::wstring& Key, const std::wstring& FileName, const std::string& EntryPoint);

	ID3D11InputLayout* GetInputLayoutByKey(const std::wstring& Key) const;
	ID3D11VertexShader* GetVertexShaderByKey(const std::wstring& Key) const;
	ID3D11PixelShader* GetPixelShaderByKey(const std::wstring& Key) const;

private:
	TMap<std::wstring, ID3D11InputLayout*> InputLayouts;
	TMap<std::wstring, ID3D11VertexShader*> VertexShaders;
	TMap<std::wstring, ID3D11PixelShader*> PixelShaders;

};

