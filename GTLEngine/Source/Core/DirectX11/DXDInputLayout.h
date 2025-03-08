#pragma once

class UDXDInputLayout
{
public:
	HRESULT CreateInputLayout(ComPtr<ID3D11Device> Device, ComPtr<ID3DBlob> Blob);

	ComPtr<ID3D11InputLayout> GetInputLayout() const { return DXDInputLayout; }

private:
	ComPtr<ID3D11InputLayout> DXDInputLayout;

};

