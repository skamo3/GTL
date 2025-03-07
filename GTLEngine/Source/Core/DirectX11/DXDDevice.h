#pragma once

class UDXDDevice
{

public:
	UDXDDevice() = default;
	~UDXDDevice();

	HRESULT CreateDeviceAndContext();
	void ReleaseDeviceAndContext();

public:
	ComPtr<ID3D11Device> GetDevice() const { return Device; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() const { return DeviceContext; }

private:
	ComPtr<ID3D11Device> Device = nullptr;
	ComPtr<ID3D11DeviceContext> DeviceContext = nullptr;

};

