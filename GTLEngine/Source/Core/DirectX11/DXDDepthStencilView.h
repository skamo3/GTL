#pragma once

class UDXDDepthStencilView
{
public:
	UDXDDepthStencilView() = default;
	~UDXDDepthStencilView();

	HRESULT CreateDepthStencilView(ComPtr<ID3D11Device> DXDDevice, HWND hWnd);
	void ReleaseDepthStencilView();

	ComPtr<ID3D11DepthStencilView> GetDepthStencilView() const { return DepthStencilView; }
private:
	ComPtr<ID3D11Texture2D>	DepthStencilBuffer;
	ComPtr<ID3D11DepthStencilView> DepthStencilView;
};

