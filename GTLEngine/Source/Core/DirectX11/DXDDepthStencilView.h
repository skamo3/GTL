#pragma once

class UDXDDepthStencilView
{
public:
	UDXDDepthStencilView() = default;
	~UDXDDepthStencilView();

	HRESULT CreateDepthStencilView(ComPtr<ID3D11Device> DXDDevice, HWND hWnd);
	void ReleaseDepthStencilView();

	ID3D11DepthStencilView* GetDepthStencilView() const { return DepthStencilView; }
private:
	ID3D11Texture2D*	DepthStencilBuffer;
	ID3D11DepthStencilView* DepthStencilView;
};

