#pragma once

class UDXDDevice;
class UDXDSwapChain;
class UDXDRenderTarget;
class UDXDDepthStencilView;
class UDXDRasterizerState;
class UDXDShaderManager;
class UDXDInputLayout;

class UObject;

class UDirectXHandle
{
public:
	UDirectXHandle() = default;
	~UDirectXHandle();


private:
	HRESULT CreateDeviceAndSwapchain();

public:
	HRESULT CreateDirectX11Handle(HWND hWnd);
	void ReleaseDirectX11Handle();

	void PrepareRender();
	//void Render(TArray<UObject> Objs);

	HWND GetWindowHandle() const { return WindowHandle; }

private:
	HWND WindowHandle;
	D3D11_VIEWPORT ViewportInfo;

public:
	void AddRenderTarget(string TargetName, const D3D11_RENDER_TARGET_VIEW_DESC& RenderTargetViewDesc);

public:
	ComPtr<ID3D11Device>	GetD3DDevice() const { return DXDDevice; }
	ComPtr<ID3D11DeviceContext> GetD3DDeviceContext() const { return DXDDeviceContext; }
	ComPtr<IDXGISwapChain> GetDXDSwapChain() const { return DXDSwapChain; }

private:
	ComPtr<ID3D11Device> DXDDevice;
	ComPtr<ID3D11DeviceContext> DXDDeviceContext;
	ComPtr<IDXGISwapChain> DXDSwapChain;

	map<string, shared_ptr<UDXDRenderTarget>>		RenderTarget;
	shared_ptr<UDXDDepthStencilView>	DepthStencilView; // 여러개 보류.
	shared_ptr<UDXDRasterizerState>		RasterizerState; // 여러개 보류.
	shared_ptr<UDXDShaderManager>			ShaderManager;

	shared_ptr<UDXDInputLayout> InputLayout;

};
