#pragma once

class UDXDDevice;

class UDXDSwapChain
{
public:
	UDXDSwapChain() = default;
	~UDXDSwapChain();

public:
	HRESULT CreateSwapChain(HWND hWnd, shared_ptr<UDXDDevice> Device, D3D11_VIEWPORT& ViewportInfo);
	void ReleaseSwapChain();

	void Present();
	void Resize();


	ComPtr<IDXGISwapChain> GetSwapChain() const { return SwapChain; }
private:
	ComPtr<IDXGISwapChain> SwapChain;
};

