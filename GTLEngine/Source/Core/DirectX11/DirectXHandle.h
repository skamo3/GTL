#pragma once

#include "Resource/VertexTypes.h"

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
class UGizmo;

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
	void RenderGizmo(UObject* Selected, UGizmo* Gizmo);
	void RenderObejct(const TArray<AActor*> Actors);

private:
	void InitView();


private:
	D3D11_VIEWPORT ViewportInfo;

public:
	HRESULT AddRenderTarget(std::wstring TargetName, const D3D11_RENDER_TARGET_VIEW_DESC& RenderTargetViewDesc);

public:
	ComPtr<ID3D11Device>	GetD3DDevice() const { return DXDDevice; }
	ComPtr<ID3D11DeviceContext> GetD3DDeviceContext() const { return DXDDeviceContext; }
	ComPtr<IDXGISwapChain> GetDXDSwapChain() const { return DXDSwapChain; }

	void AddNormalVertexBuffer(const TArray<FVertexSimple>& vertices);
	void AddLineVertexBuffer(const TArray<FVertexSimple>& vertices);
	void AddConstantBuffer(const std::wstring& Key, const TArray<FVertexSimple>& vertices);

private:
	ComPtr<ID3D11Device> DXDDevice;
	ComPtr<ID3D11DeviceContext> DXDDeviceContext;
	ComPtr<IDXGISwapChain> DXDSwapChain;

	TMap<std::wstring, UDXDRenderTarget*> RenderTarget;
	UDXDDepthStencilView* DepthStencilView; // 여러개 보류.
	UDXDRasterizerState* RasterizerState; // 여러개 보류.
	UDXDShaderManager* ShaderManager;

	TMap<std::wstring, ID3D11Buffer*> VertexBuffer;
	TMap<std::wstring, ID3D11Buffer*> ConstantBuffer;
};
