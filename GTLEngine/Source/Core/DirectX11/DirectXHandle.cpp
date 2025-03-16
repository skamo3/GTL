#include "pch.h"
#include "DirectXHandle.h"

#include "DXDRenderTarget.h"
#include "DXDDepthStencilView.h"
#include "DXDRasterizerState.h"
#include "DXDShaderManager.h"
#include "DXDConstantBuffer.h"

#include "CoreUObject/GameFrameWork/Actor.h"
#include "CoreUObject/GameFrameWork/Camera.h"

#include "CoreUObject/Components/PrimitiveComponent.h"
#include "CoreUObject/Components/CameraComponent.h"
#include "CoreUObject/Components/LineComponent.h"

#include "Engine.h"

#include "Gizmo/GizmoManager.h"
#include "World.h"

#include "Math/Matrix.h"

#include "DirectXTex/DirectXTex.h"
#include "DirectXTex/DirectXTex.inl"

UDirectXHandle::~UDirectXHandle()
{
	ReleaseDirectX11Handle();
}

HRESULT UDirectXHandle::CreateDeviceAndSwapchain()
{
	D3D_FEATURE_LEVEL FeatureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

    DXGI_SWAP_CHAIN_DESC swapchaindesc = {};
    swapchaindesc.BufferDesc.Width = UEngine::GetEngine().GetWindowInfo().Width; // 창 크기에 맞게 자동으로 설정
    swapchaindesc.BufferDesc.Height = UEngine::GetEngine().GetWindowInfo().Height; // 창 크기에 맞게 자동으로 설정
    swapchaindesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // 색상 포맷
    swapchaindesc.SampleDesc.Count = 1; // 멀티 샘플링 비활성화
    swapchaindesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 렌더 타겟으로 사용
    swapchaindesc.BufferCount = 2; // 더블 버퍼링
    swapchaindesc.OutputWindow = UEngine::GetEngine().GetWindowInfo().WindowHandle; // 렌더링할 창 핸들
    swapchaindesc.Windowed = TRUE; // 창 모드
    swapchaindesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // 스왑 방식

	uint CreateDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG;

	// Direct3D 장치와 스왑 체인을 생성
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, CreateDeviceFlags, FeatureLevels, ARRAYSIZE(FeatureLevels), D3D11_SDK_VERSION, &swapchaindesc, &DXDSwapChain, &DXDDevice, nullptr, &DXDDeviceContext);

	if (FAILED(hr))
		return hr;

	// 생성된 스왑 체인의 정보 가져오기
	DXDSwapChain->GetDesc(&swapchaindesc);

	// 뷰포트 정보 설정
	ViewportInfo = { 0.0f, 0.0f, (float)swapchaindesc.BufferDesc.Width, (float)swapchaindesc.BufferDesc.Height, 0.0f, 1.0f };

	return S_OK;
}

HRESULT UDirectXHandle::CreateShaderManager()
{
	ShaderManager = new UDXDShaderManager(DXDDevice);
	if (ShaderManager == nullptr)
		return S_FALSE;

    // Primitive VS, PS, InputLayout 생성.
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    HRESULT hr = ShaderManager->AddVertexShaderAndInputLayout(L"DefaultVS", L"Resource/Shader/PrimitiveShader.hlsl", "mainVS", layout, ARRAYSIZE(layout));
    if (FAILED(hr))
        return hr;

    hr = ShaderManager->AddPixelShader(L"DefaultPS", L"Resource/Shader/PrimitiveShader.hlsl", "mainPS");
    if (FAILED(hr))
        return hr;

    // Texture VS, PS, InputLayout 생성.
    D3D11_INPUT_ELEMENT_DESC TextureLayout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    hr = ShaderManager->AddVertexShaderAndInputLayout(L"TextureVS", L"Resource/Shader/TextureShader.hlsl", "mainVS", TextureLayout, ARRAYSIZE(TextureLayout));
    if (FAILED(hr))
        return hr;

    hr = ShaderManager->AddPixelShader(L"TexturePS", L"Resource/Shader/TextureShader.hlsl", "mainPS");
    if (FAILED(hr))
        return hr;

	D3D11_SAMPLER_DESC SamplerDesc = {};
    SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.MipLODBias = -1.0f;

	SamplerDesc.MaxAnisotropy = 16;
	SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	SamplerDesc.MinLOD = 0;
	SamplerDesc.MaxLOD = 0;
    
	hr = DXDDevice->CreateSamplerState(&SamplerDesc, &FontSamplerState);
	if (FAILED(hr))
		return hr;

    return S_OK;
}

HRESULT UDirectXHandle::CreateDirectX11Handle(HWND hWnd)
{
	HRESULT hr;
	// 디바이스 및 스왑체인 생성.
	hr = CreateDeviceAndSwapchain();
	if (FAILED(hr))
		return hr;

	// 래스터라이저 스테이트 생성.
	{
		// 일반 메시용 레스터라이저
		UDXDRasterizerState* NormalRasterizer = new UDXDRasterizerState();
		if (NormalRasterizer == nullptr)
			return S_FALSE;
		D3D11_RASTERIZER_DESC NormalRasterizerDesc = {};
		NormalRasterizerDesc.FillMode = D3D11_FILL_SOLID; // 채우기 모드
		NormalRasterizerDesc.CullMode = D3D11_CULL_BACK; // 백 페이스 컬링
		hr = NormalRasterizer->CreateRasterizerState(DXDDevice, &NormalRasterizerDesc);
		if (FAILED(hr))
			return hr;
		RasterizerStates[TEXT("Normal")] = NormalRasterizer;
	}
	{
		// 기즈모 레스터라이저
		UDXDRasterizerState* GizmoRasterizer = new UDXDRasterizerState();
		if (GizmoRasterizer == nullptr)
			return S_FALSE;
		D3D11_RASTERIZER_DESC GizmoRasterizerDesc = {};
		GizmoRasterizerDesc.FillMode = D3D11_FILL_SOLID; // 채우기 모드
		GizmoRasterizerDesc.CullMode = D3D11_CULL_FRONT; // 백 페이스 컬링
		hr = GizmoRasterizer->CreateRasterizerState(DXDDevice, &GizmoRasterizerDesc);
		if (FAILED(hr))
			return hr;
		RasterizerStates[TEXT("Gizmo")] = GizmoRasterizer;
	}

	// 셰이더 초기화. VertexShader, PixelShader, InputLayout 생성.
	// VertexShader, InputLayout 는 쌍으로 생성 및 이름으로 관리.
	hr = CreateShaderManager();

	// 상수 버퍼 생성 및 버텍스 쉐이더와 픽셀 쉐이더에 바인딩
	for (uint32 i = 0; i < static_cast<uint32>(EConstantBufferType::Max); i++)
	{
		EConstantBufferType Type = static_cast<EConstantBufferType>(i);
		if (Type == EConstantBufferType::None)
		{
			continue;
		}

		hr = AddConstantBuffer(Type);
		if (FAILED(hr))
		{
			return hr;
		}
	}

	// 쉐이더에 상수 버퍼 바인딩
	if (UDXDConstantBuffer* DXDCB = ConstantBuffers[EConstantBufferType::ChangesOnResize])
	{
		if (ID3D11Buffer* CbChangedOnResize = DXDCB->GetConstantBuffer())
		{
			DXDDeviceContext->VSSetConstantBuffers(0, 1, &CbChangedOnResize);
		}
	}
	if (UDXDConstantBuffer* DXDCB = ConstantBuffers[EConstantBufferType::ChangesEveryFrame])
	{
		if (ID3D11Buffer* CbChangesEveryFrame = DXDCB->GetConstantBuffer())
		{
			DXDDeviceContext->VSSetConstantBuffers(1, 1, &CbChangesEveryFrame);
		}
	}
	if (UDXDConstantBuffer* DXDCB = ConstantBuffers[EConstantBufferType::ChangesEveryObject])
	{
		if (ID3D11Buffer* CbChangesEveryObject = DXDCB->GetConstantBuffer())
		{
			DXDDeviceContext->VSSetConstantBuffers(2, 1, &CbChangesEveryObject);
		}
	}
	if (UDXDConstantBuffer* DXDCB = ConstantBuffers[EConstantBufferType::MVP])
	{
		if (ID3D11Buffer* CbMVP = DXDCB->GetConstantBuffer())
		{
			DXDDeviceContext->VSSetConstantBuffers(3, 1, &CbMVP);
		}
	}

    // 뎁스 스텐실 뷰 생성.
    DepthStencilView = new UDXDDepthStencilView();
    FWindowInfo winInfo = UEngine::GetEngine().GetWindowInfo();
    hr = DepthStencilView->CreateDepthStencilView(DXDDevice, winInfo.WindowHandle, static_cast<float>(winInfo.Width), static_cast<float>(winInfo.Height));
    if (FAILED(hr))
        return hr;

	/**
	* TODO: 뎁스 스텐실 스테이트 생성 권장.
	*       생성하지 않는 경우 기본값이 적용되므로, 현재 프로젝트에서는 따로 생성하지 않아도 됨.
	*       기본값:
	*         깊이 테스트 = TRUE
	*         깊이 비교 함수 = LESS (깊이값이 더 작을 때만 그려짐. 즉 더 가까이 있는 경우)
	*         깊이 쓰기 = TRUE
	*         스텐실 테스트 = FALSE
	*/

    // 텍스쳐 불러오기.
    // TODO: 텍스쳐 클래스로 묶기
	// Create 시에는 File 경로로 불러오기.
    // 내부에서 map<string,SRV> 쌍으로 관리.
    DirectX::ScratchImage TextureImage;

	hr =  DirectX::LoadFromDDSFile(L"Resource/Texture/Fonts/DejaVu_Sans_Mono.dds", DirectX::DDS_FLAGS_NONE, nullptr, TextureImage);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = DirectX::CreateShaderResourceView(DXDDevice, TextureImage.GetImages(), TextureImage.GetImageCount(), TextureImage.GetMetadata(), &FontAtlasTexture);
	if (FAILED(hr))
	{
		return hr;
	}



    return S_OK;
}

void UDirectXHandle::ReleaseDirectX11Handle()
{
	if (DXDDeviceContext)
	{
		DXDDeviceContext->Flush();
		DXDDeviceContext->Release();
		DXDDeviceContext = nullptr;
	}

	if (DXDDevice)
	{
		DXDDevice->Release();
		DXDDevice = nullptr;
	}

	if (DXDSwapChain)
	{
		DXDSwapChain->Release();
		DXDSwapChain = nullptr;
	}

	RenderTarget->ReleaseRenderTarget();

	ShaderManager->ReleaseAllShader();
}

void UDirectXHandle::UpdateCameraMatrix(ACamera* Camera)
{
	// Camera->GetCameraComponent.
	// MVP 계산 행렬 구하고
	// 카메라 상수버퍼로 바로 전달.
	if (!Camera)
	{
		return;
	}

	// 카메라 View 변환.
	// 카메라 컴포넌트의 로컬 트랜스폼은 변경되지 않는다고 가정
	ID3D11Buffer* CbChangesEveryFrame = ConstantBuffers[EConstantBufferType::ChangesEveryFrame]->GetConstantBuffer();
	if (!CbChangesEveryFrame)
	{
		return;
	}
	D3D11_MAPPED_SUBRESOURCE viewMappedData;
	DXDDeviceContext->Map(CbChangesEveryFrame, 0, D3D11_MAP_WRITE_DISCARD, 0, &viewMappedData);
	if (FCbChangesEveryFrame* Buffer = reinterpret_cast<FCbChangesEveryFrame*>(viewMappedData.pData))
	{
		UpdateWorldViewMatrix(Camera);
		Buffer->ViewMatrix = UEngine::GetEngine().GetWorld()->GetViewMatrix();
	}
	DXDDeviceContext->Unmap(CbChangesEveryFrame, 0);

    // 카메라 Projection 변환
    // TODO: Test. 프로젝션 matrix는 리사이즈 할 때, FOV 변환할 때.
    ID3D11Buffer* CbChangesOnResize = ConstantBuffers[EConstantBufferType::ChangesOnResize]->GetConstantBuffer();
    if (!CbChangesOnResize )
    {
        return;
    }
    D3D11_MAPPED_SUBRESOURCE projectionMappedData;
    DXDDeviceContext->Map(CbChangesOnResize, 0, D3D11_MAP_WRITE_DISCARD, 0, &projectionMappedData);
    if (FCbChangesOnResize* Buffer = reinterpret_cast<FCbChangesOnResize*>(projectionMappedData.pData))
    {
        UpdateWorldProjectionMatrix(Camera);
		Buffer->ProjectionMatrix = UEngine::GetEngine().GetWorld()->GetProjectionMatrix();
	}
	DXDDeviceContext->Unmap(CbChangesOnResize, 0);
	//XMMatrixTranspose(XMMatrixPerspectiveFovLH(XMConvertToRadians(60.f), Width / Height, 1.f, 1000.f));
}

// use when D3D11_PRIMITIVE_TOPOLOGY_LINELIST state
void UDirectXHandle::RenderWorldPlane(ACamera* Camera) {

    /** state check
    D3D11_PRIMITIVE_TOPOLOGY topology;
    DXDDeviceContext->IAGetPrimitiveTopology(&topology);
    if ( topology != D3D11_PRIMITIVE_TOPOLOGY_LINELIST )
        DXDDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    */

    // set position
    FVector campos = Camera->GetActorLocation();
    FVector truncpos = FVector(floor(campos.X), floor(campos.Y), 0.f);

    ID3D11Buffer* CbChangesEveryObject = ConstantBuffers[EConstantBufferType::ChangesEveryObject]->GetConstantBuffer();
    if ( !CbChangesEveryObject ) {
        return;
    }
    D3D11_MAPPED_SUBRESOURCE MappedData = {};
    DXDDeviceContext->Map(CbChangesEveryObject, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedData);
    if ( FCbChangesEveryObject* Buffer = reinterpret_cast<FCbChangesEveryObject*>(MappedData.pData) ) {
        Buffer->WorldMatrix = FMatrix::GetScaleMatrix(FVector(2, 2, 0)) * FMatrix::GetTranslateMatrix(truncpos * 2);
    }
    DXDDeviceContext->Unmap(CbChangesEveryObject, 0);

    uint Stride = sizeof(FVertexSimple);
    uint offset = 0;
    FVertexInfo Info = PrimitiveVertexBuffers[EPrimitiveType::Grid];
    ID3D11Buffer* VB = Info.VertexBuffer;
    uint Num = Info.NumVertices;
    DXDDeviceContext->IASetVertexBuffers(0, 1, &VB, &Stride, &offset);
    DXDDeviceContext->Draw(Num, 0);

}

void UDirectXHandle::RenderGizmo(UObject* Selected, UGizmoManager* GizmoManager)
{
	// Selected 오브젝트 기반으로 기즈모 그리가.

    switch (GizmoManager->GetGizmoType())
    {
	case EGizmoType::Translate: // 이동 모양 그리기.
        break;
	case EGizmoType::Rotate: // 회전 모양 그리기.
        break;
	case EGizmoType::Scale: // 크기 조절 모양 그리기.
        break;
    default:
        break;
    }
}

void UDirectXHandle::RenderPrimitive(UPrimitiveComponent* PrimitiveComp)
{
    if (!PrimitiveComp)
        return;

    switch ( PrimitiveComp->GetPrimitiveType() ) {
    case EPrimitiveType::None:
    case EPrimitiveType::Line:
    case EPrimitiveType::Grid:
        return;
    default:
        break;
    }

    DXDDeviceContext->VSSetShader(ShaderManager->GetVertexShaderByKey(TEXT("DefaultVS")), NULL, 0);
    DXDDeviceContext->PSSetShader(ShaderManager->GetPixelShaderByKey(TEXT("DefaultPS")), NULL, 0);

    DXDDeviceContext->IASetInputLayout(ShaderManager->GetInputLayoutByKey(TEXT("DefaultVS")));

    // Begin Object Matrix Update. 
    ID3D11Buffer* CbChangesEveryObject = ConstantBuffers[EConstantBufferType::ChangesEveryObject]->GetConstantBuffer();
    if (!CbChangesEveryObject)
    {
        return;
    }
    D3D11_MAPPED_SUBRESOURCE MappedData = {};
    DXDDeviceContext->Map(CbChangesEveryObject, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedData);
    if (FCbChangesEveryObject* Buffer = reinterpret_cast<FCbChangesEveryObject*>(MappedData.pData))
    {
        Buffer->WorldMatrix = PrimitiveComp->GetWorldMatrix();
    }
    DXDDeviceContext->Unmap(CbChangesEveryObject, 0);

    EPrimitiveType Type = PrimitiveComp->GetPrimitiveType();
    uint Stride = sizeof(FVertexSimple);
    //uint Stride = 84;6
    UINT offset = 0;
    FVertexInfo Info = PrimitiveVertexBuffers[Type];
    ID3D11Buffer* VB = Info.VertexBuffer;
    uint Num = Info.NumVertices;
    DXDDeviceContext->IASetVertexBuffers(0, 1, &VB, &Stride, &offset);

    // IndexBuffer가 존재하는지 확인하고, DrawIndexed 호출
    auto indexIt = PrimitiveIndexBuffers.find(Type);
    if (indexIt != PrimitiveIndexBuffers.end())
    {
        FIndexInfo IndexInfo = indexIt->second;
        DXDDeviceContext->IASetIndexBuffer(IndexInfo.IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
        DXDDeviceContext->DrawIndexed(IndexInfo.NumIndices, 0, 0);
    }
    else
    {
        DXDDeviceContext->Draw(Num, 0);
    }
}

void UDirectXHandle::RenderAABB(FAABB aabb) {
    // Begin Object Matrix Update. 
    ID3D11Buffer* CbChangesEveryObject = ConstantBuffers[EConstantBufferType::ChangesEveryObject]->GetConstantBuffer();
    if ( !CbChangesEveryObject ) {
        return;
    }
    D3D11_MAPPED_SUBRESOURCE MappedData = {};
    DXDDeviceContext->Map(CbChangesEveryObject, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedData);
    if ( FCbChangesEveryObject* Buffer = reinterpret_cast<FCbChangesEveryObject*>(MappedData.pData) ) {
        FVector AABBScale = aabb.GetGap();
        FVector AABBLocation = aabb.min;

        FMatrix ScaleMatrix = FMatrix::GetScaleMatrix(AABBScale); // 크기.
        FMatrix TranslationMatrix = FMatrix::GetTranslateMatrix(AABBLocation); // 위치.

        FMatrix WorldMatrix = ScaleMatrix * TranslationMatrix;
        Buffer->WorldMatrix = WorldMatrix;
    }
    DXDDeviceContext->Unmap(CbChangesEveryObject, 0);

    uint Stride = sizeof(FVertexSimple);
    UINT offset = 0;
    FVertexInfo Info = PrimitiveVertexBuffers[EPrimitiveType::BoundingBox];
    ID3D11Buffer* VB = Info.VertexBuffer;
    uint Num = Info.NumVertices;
    DXDDeviceContext->IASetVertexBuffers(0, 1, &VB, &Stride, &offset);

    DXDDeviceContext->Draw(Num, 0);
}

void UDirectXHandle::RenderBoundingBox(const TArray<AActor*> Actors) {

    for ( AActor* Actor : Actors ) {
        if (Actor->IsSelected)
            RenderAABB(Actor->GetAABB());
    }
    RenderAABB(FAABB(FVector(-0.5, -0.5, -0.5), FVector(0.5, 0.5, 0.5)));
}

void UDirectXHandle::RenderObject(const TArray<AActor*> Actors)
{

    for (AActor* Actor : Actors)
    {
        for (UActorComponent* Comp : Actor->GetOwnedComponent())
        {
			//RenderUUID(dynamic_cast<UPrimitiveComponent*>(Comp));
            RenderPrimitive(dynamic_cast<UPrimitiveComponent*>(Comp));
        }

		// 액터가 가진 모든 컴포넌트 순회하면서 렌더링.
		//RenderPrimitive(Actor->GetComponentByClass<UPrimitiveComponent>());
		// PrimitiveComponent가 없으면 그릴 게 없으므로 Pass;
	}


    // 셰이더 준비.
    // 현재 액터가 가진 Component 타입 별로 분석해서 셰이더 적용.
    // 컴포넌트에서 정보 가져와서 Constant 버퍼 업데이트.
    // 액터에 해당하는 오브젝트 렌더링.
    
}

void UDirectXHandle::RenderLines(const TArray<AActor*> Actors)
{

	UINT stride = sizeof(FCbLine);
	UINT offset = 0;

    // TODO: 인풋 레이아웃을 line 전용으로 변경해야하는데 지금은 동일한 정보이므로 바꾸지 않아도 될듯함.
    //       for 루프로 순회하면서 버텍스 버퍼 업데이트 및 draw.
    

    for ( AActor* Actor : Actors ) {
        for ( UActorComponent* Comp : Actor->GetOwnedComponent() ) {
            RenderLine(dynamic_cast<ULineComponent*>(Comp));
        }

        // 액터가 가진 모든 컴포넌트 순회하면서 렌더링.
        //RenderPrimitive(Actor->GetComponentByClass<UPrimitiveComponent>());
        // PrimitiveComponent가 없으면 그릴 게 없으므로 Pass;
    }
    //
}

void UDirectXHandle::RenderLine(ULineComponent* LineComp) {
    if ( LineComp == nullptr)
        return;

	if (LineComp->GetPrimitiveType() == EPrimitiveType::None)
		return;

    DXDDeviceContext->VSSetShader(ShaderManager->GetVertexShaderByKey(TEXT("DefaultVS")), NULL, 0);
    DXDDeviceContext->PSSetShader(ShaderManager->GetPixelShaderByKey(TEXT("DefaultPS")), NULL, 0);

    DXDDeviceContext->IASetInputLayout(ShaderManager->GetInputLayoutByKey(TEXT("DefaultVS")));

    // Begin Object Matrix Update. 
    ID3D11Buffer* CbChangesEveryObject = ConstantBuffers[EConstantBufferType::ChangesEveryObject]->GetConstantBuffer();
    if ( !CbChangesEveryObject ) {
        return;
    }
    D3D11_MAPPED_SUBRESOURCE MappedData = {};
    DXDDeviceContext->Map(CbChangesEveryObject, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedData);
    if ( FCbChangesEveryObject* Buffer = reinterpret_cast<FCbChangesEveryObject*>(MappedData.pData) ) {
        Buffer->WorldMatrix = LineComp->GetWorldMatrix();
    }
    DXDDeviceContext->Unmap(CbChangesEveryObject, 0);

    // View 변환 Constant.

    // Projection 변환 Constant.


    // End Object Matrix Update


    EPrimitiveType Type = LineComp->GetPrimitiveType();
    uint Stride = sizeof(FVertexSimple);
    UINT offset = 0;
    FVertexInfo Info = PrimitiveVertexBuffers[Type];
    ID3D11Buffer* VB = Info.VertexBuffer;
    uint Num = Info.NumVertices;
    DXDDeviceContext->IASetVertexBuffers(0, 1, &VB, &Stride, &offset);

    DXDDeviceContext->Draw(Num, 0);
}

void UDirectXHandle::RenderUUID(UPrimitiveComponent* PrimitiveComp)
{
    if (!PrimitiveComp)
        return;

    switch (PrimitiveComp->GetPrimitiveType()) {
    case EPrimitiveType::None:
    case EPrimitiveType::Line:
    case EPrimitiveType::Grid:
        return;
    default:
        break;
    }

    // Begin Object Matrix Update. 
    ID3D11Buffer* CbChangesEveryObject = ConstantBuffers[EConstantBufferType::ChangesEveryObject]->GetConstantBuffer();
    if (!CbChangesEveryObject)
    {
        return;
    }
    D3D11_MAPPED_SUBRESOURCE MappedData = {};
    DXDDeviceContext->Map(CbChangesEveryObject, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedData);
    if (FCbChangesEveryObject* Buffer = reinterpret_cast<FCbChangesEveryObject*>(MappedData.pData))
    {
        // 프리미티브 위치에서 카메라 쪽으로 회전.
		FVector CameraLocation = UEngine::GetEngine().GetWorld()->GetCamera()->GetActorLocation();
		FVector PrimitiveLocation = PrimitiveComp->GetOwner()->GetActorLocation();
		FVector Delta = CameraLocation - PrimitiveLocation;
		Delta = Delta.GetSafeNormal();

		float Pitch = FMath::RadiansToDegrees(FMath::Asin(Delta.Z));
		float Yaw = FMath::RadiansToDegrees(FMath::Atan2(Delta.Y, Delta.X));

		FRotator PrimitiveRotation(Pitch, Yaw, 0.f);
        FMatrix RotationMatrix(PrimitiveRotation);
        FMatrix TranslationMatrix = FMatrix::GetTranslateMatrix(PrimitiveLocation);

        Buffer->WorldMatrix = RotationMatrix * TranslationMatrix;
    }
    DXDDeviceContext->Unmap(CbChangesEveryObject, 0);

    DXDDeviceContext->VSSetShader(ShaderManager->GetVertexShaderByKey(TEXT("TextureVS")), NULL, 0);
    DXDDeviceContext->PSSetShader(ShaderManager->GetPixelShaderByKey(TEXT("TexturePS")), NULL, 0);
    DXDDeviceContext->IASetInputLayout(ShaderManager->GetInputLayoutByKey(TEXT("TextureVS")));

	DXDDeviceContext->PSSetShaderResources(0, 1, &FontAtlasTexture);
	DXDDeviceContext->PSSetSamplers(0, 1, &FontSamplerState);

    //EPrimitiveType Type = LineComp->GetPrimitiveType();
    uint Stride = sizeof(FVertexUV);
    UINT offset = 0;
    FVertexInfo Info = VertexBuffers[L"FontAtlas"];
    ID3D11Buffer* VB = Info.VertexBuffer;
    uint Num = Info.NumVertices;
    DXDDeviceContext->IASetVertexBuffers(0, 1, &VB, &Stride, &offset);

    DXDDeviceContext->Draw(Num, 0);
}


void UDirectXHandle::InitView()
{
	// 렌더 타겟 클리어 및 클리어에 적용할 색.
	FLOAT ClearColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };

	DXDDeviceContext->ClearRenderTargetView(RenderTarget->GetFrameBufferRTV().Get(), ClearColor);

	// 뎁스/스텐실 뷰 클리어. 뷰, DEPTH만 클리어, 깊이 버퍼 클리어 할 값, 스텐실 버퍼 클리어 할 값.
	DXDDeviceContext->ClearDepthStencilView(DepthStencilView->GetDepthStencilView(), D3D11_CLEAR_DEPTH, 1.0f, 0);

    //DXDDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DXDDeviceContext->RSSetViewports(1, &ViewportInfo);
	DXDDeviceContext->RSSetState(RasterizerStates[TEXT("Normal")]->GetRasterizerState().Get());

	// TODO: SwapChain Window 크기와 DepthStencilView Window 크기가 맞아야 에러 X.
	DXDDeviceContext->OMSetRenderTargets(1, RenderTarget->GetFrameBufferRTV().GetAddressOf(), DepthStencilView->GetDepthStencilView());
}

HRESULT UDirectXHandle::AddRenderTarget(std::wstring TargetName, const D3D11_RENDER_TARGET_VIEW_DESC& RenderTargetViewDesc)
{
	RenderTarget = new UDXDRenderTarget();

	HRESULT hr = RenderTarget->CreateRenderTarget(DXDDevice, DXDSwapChain, RenderTargetViewDesc);
	if (FAILED(hr))
		return hr;

	return S_OK;
}

HRESULT UDirectXHandle::AddPrimitiveVertexBuffer(EPrimitiveType KeyType, const TArray<FVertexSimple> vertices, const TArray<uint32>& indices)
{
	ID3D11Buffer* NewVertexBuffer;
	// Primitive 버텍스 버퍼 생성
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(FVertexSimple) * static_cast<uint32>(vertices.size());
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices.data();

	HRESULT hr = DXDDevice->CreateBuffer(&bufferDesc, &initData, &NewVertexBuffer);
	if (FAILED(hr))
		return hr;

	FVertexInfo VertexInfo = { static_cast<uint32>(vertices.size()), NewVertexBuffer };
	PrimitiveVertexBuffers.insert({ KeyType, VertexInfo });

	if (indices.size() > 0)
	{
		ID3D11Buffer* NewIndexBuffer = nullptr;
		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(uint32) * static_cast<uint32>(indices.size());
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA indexInitData = {};
		indexInitData.pSysMem = indices.data();

		hr = DXDDevice->CreateBuffer(&indexBufferDesc, &indexInitData, &NewIndexBuffer);
		if (FAILED(hr))
			return hr;

		FIndexInfo IndexInfo = { static_cast<uint32>(indices.size()), NewIndexBuffer };
		PrimitiveIndexBuffers.insert({ KeyType, IndexInfo });
	}

	return S_OK;
}

HRESULT UDirectXHandle::AddGizmoVertexBuffer(EGizmoViewType KeyType, const TArray<FVertexSimple> vertices, const TArray<uint32>& indices)
{
	ID3D11Buffer* NewVertexBuffer;
	// Gizmo 버텍스 버퍼 생성
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(FVertexSimple) * static_cast<uint32>(vertices.size());
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices.data();

	HRESULT hr = DXDDevice->CreateBuffer(&bufferDesc, &initData, &NewVertexBuffer);
	if (FAILED(hr))
		return hr;

	FVertexInfo VertexInfo = { static_cast<uint32>(vertices.size()), NewVertexBuffer };
	GizmoVertexBuffers.insert({ KeyType, VertexInfo });

	if (indices.size() > 0)
	{
		ID3D11Buffer* NewIndexBuffer = nullptr;
		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(uint32) * static_cast<uint32>(indices.size());
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA indexInitData = {};
		indexInitData.pSysMem = indices.data();

		hr = DXDDevice->CreateBuffer(&indexBufferDesc, &indexInitData, &NewIndexBuffer);
		if (FAILED(hr))
			return hr;

		FIndexInfo IndexInfo = { static_cast<uint32>(indices.size()), NewIndexBuffer };
		GizmoIndexBuffers.insert({ KeyType, IndexInfo });
	}

	return S_OK;
}

HRESULT UDirectXHandle::AddConstantBuffer(EConstantBufferType Type)
{
	UDXDConstantBuffer* NewConstantBuffer = new UDXDConstantBuffer(DXDDevice);
	if (!NewConstantBuffer)
	{
		return S_FALSE;
	}

	HRESULT hr = S_OK;

	hr = NewConstantBuffer->CreateBuffer(Type);
	if (FAILED(hr))
	{
		return hr;
	}

	ConstantBuffers.insert({ Type, NewConstantBuffer });

	return S_OK;
}

void UDirectXHandle::UpdateWorldViewMatrix(ACamera* Camera)
{
	FVector CameraLocation = Camera->GetActorLocation();
	FRotator CameraRotation = Camera->GetActorRotation();

	// Rotation Matrix 생성.
	FVector ForwardVector = CameraRotation.TransformRotVecToMatrix(FVector::ForwardVector).GetSafeNormal();

	//XMMatrixLookAtLH(Eye, At, Up);
	FMatrix CameraViewMatrix = FMatrix::LookAtLH(CameraLocation, CameraLocation + ForwardVector, FVector::UpVector);
	UEngine::GetEngine().GetWorld()->SetViewMatrix(CameraViewMatrix);

}

void UDirectXHandle::UpdateWorldProjectionMatrix(ACamera* Camera)
{
	float FOVRad = FMath::DegreesToRadians(Camera->GetFieldOfView());
	UEngine::GetEngine().GetWorld()->SetProjectionMatrix(
		FMatrix::PerspectiveFovLH(FOVRad, ViewportInfo.Width / ViewportInfo.Height, Camera->GetNearClip(), Camera->GetFarClip())
	);
}


