#include "pch.h"
#include "DXDInputLayout.h"

HRESULT UDXDInputLayout::CreateInputLayout(ComPtr<ID3D11Device> Device, ComPtr<ID3DBlob> Blob)
{
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        // D3D10_APPEND_ALIGNED_ELEMENT
    };

	Device->CreateInputLayout(layout, ARRAYSIZE(layout), Blob->GetBufferPointer(), Blob->GetBufferSize(), &DXDInputLayout);
	return S_OK;
}
