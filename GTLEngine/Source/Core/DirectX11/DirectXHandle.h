#pragma once

class UDXDDevice;
class UDXDSwapChain;
class UDXDRenderTarget;
class UDXDDepthStencilView;
class UDXDRasterizerState;
class UDXDShaderManager;
class UDXDInputLayout;

class UDirectXHandle
{
public:
	UDirectXHandle() = default;
	~UDirectXHandle();

	HRESULT CreateDirectX11Handle();
	void ReleaseDirectX11Handle();

	void PrepareRender();
	void Render();

	FWindowInfo GetWindowInfo() const { return WindowInfo; }

private:
	FWindowInfo WindowInfo;
	D3D11_VIEWPORT ViewportInfo;

public:
	void AddRenderTarget(string TargetName, const D3D11_RENDER_TARGET_VIEW_DESC& RenderTargetViewDesc);

public:
	shared_ptr<UDXDDevice>	GetD3DDevice() const { return DXDDevice; }
	shared_ptr<UDXDSwapChain>	GetSwapChain() const { return SwapChain; }

private:
	shared_ptr<UDXDDevice>				DXDDevice;
	shared_ptr<UDXDSwapChain>			SwapChain;
	map<string, shared_ptr<UDXDRenderTarget>>		RenderTarget;
	shared_ptr<UDXDDepthStencilView>	DepthStencilView; // 여러개 보류.
	shared_ptr<UDXDRasterizerState>		RasterizerState; // 여러개 보류.
	shared_ptr<UDXDShaderManager>			ShaderManager;

	shared_ptr<UDXDInputLayout> InputLayout;

};
