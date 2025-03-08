#pragma once

class UDXDDevice;
class UDXDInputLayout;

struct FShaderInfo
{

};

class UDXDShaderManager
{
public:
	UDXDShaderManager() = default;
	UDXDShaderManager(shared_ptr<UDXDDevice> Device);

	void ReleaseAllShader();

private:
	shared_ptr<UDXDDevice> DXDDevice;

public:
	HRESULT AddVertexShader(const string& FileName, ComPtr<ID3DBlob> Blob);
	HRESULT AddPixelShader(const string& FileName);

	ComPtr<ID3D11VertexShader> GetVertexShaderByKey(const string& Name) const;
	ComPtr<ID3D11PixelShader> GetPixelShaderByKey(const string& Name) const;

private:
	// TODO: map -> TMap 으로 변경.
	map<string, ComPtr<ID3D11VertexShader>> VertexShader;
	map<string, ComPtr<ID3D11PixelShader>> PixelShader;

	// CSO : Compile Shader Object.
	ComPtr<ID3DBlob> VertexShaderCSO;
	ComPtr<ID3DBlob> PixelShaderCSO;


};

