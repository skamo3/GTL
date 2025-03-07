#pragma once

class UDXDDevice;
class UDXDSwapChain;
class UDXDRenderTarget;
class UDXDDepthStencilView;
class UDXDRasterizerState;
class UShaderManager;

class UDirectXHandle
{
public:
	UDirectXHandle() = default;
	~UDirectXHandle();

	HRESULT CreateDirectX11Handle();
	void ReleaseDirectX11Handle();

	void PrepareRender();

	FWindowInfo GetWindowInfo() const { return WindowInfo; }

private:
	FWindowInfo WindowInfo;
	D3D11_VIEWPORT ViewportInfo;

public:
	shared_ptr<UDXDDevice>	GetD3DDevice() const { return DXDDevice; }
	shared_ptr<UDXDSwapChain>	GetSwapChain() const { return SwapChain; }
	shared_ptr<UDXDRenderTarget>	GetRenderTarget() const { return RenderTarget; }

private:
	shared_ptr<UDXDDevice>				DXDDevice;
	shared_ptr<UDXDSwapChain>			SwapChain;
	shared_ptr<UDXDRenderTarget>		RenderTarget;
	shared_ptr<UDXDDepthStencilView>	DepthStencilView;
	shared_ptr<UDXDRasterizerState>		RasterizerState;

};
