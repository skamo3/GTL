#pragma once

class UDXDDevice;

class UDXDInputLayout
{
public:
	HRESULT CreateInputLayout(shared_ptr<UDXDDevice> Device, ComPtr<ID3DBlob> Blob);

	ComPtr<ID3D11InputLayout> GetInputLayout() const { return DXDInputLayout; }

private:
	ComPtr<ID3D11InputLayout> DXDInputLayout;

};

