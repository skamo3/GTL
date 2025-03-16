#pragma once

#include "Resource/Types.h"
#include <d3d11.h>
#include <d3dcompiler.h>

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
class UGizmoManager;
class UPrimitiveComponent;
class ULineComponent;

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
	void RenderWorldPlane(ACamera* Camera);
	void RenderGizmo(UObject* Selected, UGizmoManager* GizmoManager);
	void RenderPrimitive(UPrimitiveComponent* PrimitiveComp);
	void RenderBoundingBox(const TArray<AActor*> Actors);
	void RenderObject(const TArray<AActor*> Actors);
	void RenderLines(const TArray<AActor*> Actors);
	void RenderLine(ULineComponent* comp);
	inline void SetLineMode() { DXDDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST); }
	inline void SetFaceMode() { DXDDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); }
	void RenderUUID(UPrimitiveComponent* PrimitiveComp);

public:
	void InitView();


private:
	D3D11_VIEWPORT ViewportInfo;

public:
	ID3D11Device*	GetD3DDevice() const { return DXDDevice; }
	ID3D11DeviceContext* GetD3DDeviceContext() const { return DXDDeviceContext; }
	IDXGISwapChain* GetDXDSwapChain() const { return DXDSwapChain; }

	HRESULT AddRenderTarget(std::wstring TargetName, const D3D11_RENDER_TARGET_VIEW_DESC& RenderTargetViewDesc);

	HRESULT AddVertexBuffer(EPrimitiveType KeyType, const TArray<FVertexSimple> vertices, const TArray<uint32>& indices);

	// TODO: Name으로 버텍스 버퍼 저장.
	// Array 타입을 다른 방식으로 바꿔서 저장.
	template<typename T>
	HRESULT AddVertexBuffer(std::wstring KeyName, const TArray<T> vertices);

	
	HRESULT AddConstantBuffer(EConstantBufferType Type);

private:
	void UpdateWorldViewMatrix(ACamera* Camera);
	void UpdateWorldProjectionMatrix(ACamera* Camera);

	void RenderAABB(FAABB aabb);

private:
	ID3D11Device* DXDDevice;
	ID3D11DeviceContext* DXDDeviceContext;
	IDXGISwapChain* DXDSwapChain;
	
	UDXDRenderTarget* RenderTarget;
	UDXDDepthStencilView* DepthStencilView; // 여러개 보류.
	TMap<std::wstring, UDXDRasterizerState*> RasterizerStates;
	UDXDShaderManager* ShaderManager;

	TMap<EPrimitiveType, FVertexInfo> PrimitiveVertexBuffers;
	TMap<std::wstring, FVertexInfo> VertexBuffers;
	TMap<EPrimitiveType, FIndexInfo> IndexBuffers;
	TMap<EConstantBufferType, UDXDConstantBuffer*> ConstantBuffers;

	// TODO: Texture 관리용 객체로 묶어서 관리.
	ID3D11ShaderResourceView* FontAtlasTexture;
	ID3D11SamplerState* FontSamplerState;
	FVertexInfo FontTextureBuffer;


};

template<typename T>
inline HRESULT UDirectXHandle::AddVertexBuffer(std::wstring KeyName, const TArray<T> vertices)
{
	ID3D11Buffer* NewVertexBuffer;
	// 버텍스 버퍼 생성
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(T) * static_cast<uint32>(vertices.size());
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices.data();

	HRESULT hr = DXDDevice->CreateBuffer(&bufferDesc, &initData, &NewVertexBuffer);
	if (FAILED(hr))
		return hr;

	FVertexInfo Info = { static_cast<uint32>(vertices.size()), NewVertexBuffer };
	VertexBuffers.insert({ KeyName, Info });
}
