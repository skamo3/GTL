#pragma once

class UDXDDevice;
class UDXDSwapChain;
class UDXDRenderTarget;
class UDXDDepthStencilView;
class UDXDRasterizerState;
class UDXDShaderManager;
class UDXDInputLayout;

class UObject;
class AActor;
class ACamera;


struct FVertexSimple
{
	float X = 0.f, Y = 0.f, Z = 0.f;
	float R = 0.f, G = 0.f, B = 0.f, A = 1.f;
};

class UDirectXHandle
{
public:
	UDirectXHandle() = default;
	~UDirectXHandle();


private:
	HRESULT CreateDeviceAndSwapchain();
	HRESULT CreateShaderManager();

public:
	HRESULT CreateDirectX11Handle(HWND hWnd);
	void ReleaseDirectX11Handle();

	void UpdateCameraMatrix(ACamera* Camera);
	void RenderObejct(const TArray<AActor*> Actors);

private:
	void InitView();


private:
	D3D11_VIEWPORT ViewportInfo;

public:
	HRESULT AddRenderTarget(string TargetName, const D3D11_RENDER_TARGET_VIEW_DESC& RenderTargetViewDesc);

public:
	ComPtr<ID3D11Device>	GetD3DDevice() const { return DXDDevice; }
	ComPtr<ID3D11DeviceContext> GetD3DDeviceContext() const { return DXDDeviceContext; }
	ComPtr<IDXGISwapChain> GetDXDSwapChain() const { return DXDSwapChain; }

private:
	ComPtr<ID3D11Device> DXDDevice;
	ComPtr<ID3D11DeviceContext> DXDDeviceContext;
	ComPtr<IDXGISwapChain> DXDSwapChain;

	TMap<string, shared_ptr<UDXDRenderTarget>> RenderTarget;
	shared_ptr<UDXDDepthStencilView> DepthStencilView; // 여러개 보류.
	shared_ptr<UDXDRasterizerState> RasterizerState; // 여러개 보류.
	shared_ptr<UDXDShaderManager> ShaderManager;

};
