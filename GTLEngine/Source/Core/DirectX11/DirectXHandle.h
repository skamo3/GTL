#pragma once

#include "Resource/Types.h"

class UDXDDevice;
class UDXDSwapChain;
class UDXDRenderTarget;
class UDXDDepthStencilView;
class UDXDRasterizerState;
class UDXDShaderManager;
class UDXDInputLayout;
class UDXDConstantBuffer;

class UObject;
class AActor;
class ACamera;
class UGizmo;
class UPrimitiveComponent;

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
	void RenderPrimitive(UPrimitiveComponent* PrimitiveComp);
	void RenderObejct(const TArray<AActor*> Actors);

private:
	void InitView();


private:
	D3D11_VIEWPORT ViewportInfo;

public:
	ComPtr<ID3D11Device>	GetD3DDevice() const { return DXDDevice; }
	ComPtr<ID3D11DeviceContext> GetD3DDeviceContext() const { return DXDDeviceContext; }
	ComPtr<IDXGISwapChain> GetDXDSwapChain() const { return DXDSwapChain; }



	HRESULT AddRenderTarget(std::wstring TargetName, const D3D11_RENDER_TARGET_VIEW_DESC& RenderTargetViewDesc);

	void AddVertexBuffer(EPrimitiveType KeyType, const TArray<FVertexSimple>& vertices);
	
	HRESULT AddConstantBuffer(EConstantBufferType Type);

private:
	ComPtr<ID3D11Device> DXDDevice;
	ComPtr<ID3D11DeviceContext> DXDDeviceContext;
	ComPtr<IDXGISwapChain> DXDSwapChain;

	TMap<std::wstring, UDXDRenderTarget*> RenderTarget;
	UDXDDepthStencilView* DepthStencilView; // 여러개 보류.
	TMap<std::wstring, UDXDRasterizerState*> RasterizerStates;
	UDXDShaderManager* ShaderManager;

	TMap<EPrimitiveType, FVertexInfo> VertexBuffers;
	TMap<EConstantBufferType, UDXDConstantBuffer*> ConstantBuffers;
};
