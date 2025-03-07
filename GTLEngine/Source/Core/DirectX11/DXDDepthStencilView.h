#pragma once

class UDXDDevice;

class UDXDDepthStencilView
{
public:
	UDXDDepthStencilView() = default;
	~UDXDDepthStencilView();

	HRESULT CreateDepthStencilView(shared_ptr<UDXDDevice> DXDDevice);
	void ReleaseDepthStencilView();

	ComPtr<ID3D11DepthStencilView> GetDepthStencilView() const { return DepthStencilView; }
private:
	ComPtr<ID3D11Texture2D>	DepthStencilBuffer;
	ComPtr<ID3D11DepthStencilView> DepthStencilView;
};

