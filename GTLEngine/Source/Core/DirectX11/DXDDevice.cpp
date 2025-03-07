#include "pch.h"
#include "DXDDevice.h"

UDXDDevice::~UDXDDevice()
{
	ReleaseDeviceAndContext();
}

HRESULT UDXDDevice::CreateDeviceAndContext()
{
	D3D_FEATURE_LEVEL FeatureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

	uint createDeviceFlags = 0;
#ifndef _DEBUG
	createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG;
#endif
	HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, FeatureLevels, ARRAYSIZE(FeatureLevels), D3D11_SDK_VERSION, &Device, nullptr, &DeviceContext);
	if (FAILED(hr))
		return hr;
	
	return S_OK;
}

void UDXDDevice::ReleaseDeviceAndContext()
{
	if (DeviceContext)
	{
		DeviceContext->Flush();
		DeviceContext->Release();
		DeviceContext.Reset();
	}

	if (Device)
	{
		Device->Release();
		Device.Reset();
	}

}
