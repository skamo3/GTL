#include "pch.h"
#include "DXDDepthStencilState.h"

UDXDDepthStencilState::~UDXDDepthStencilState()
{
    ReleaseDepthStencilState();
}

HRESULT UDXDDepthStencilState::CreateDepthStencilState()
{


    return S_OK;
}

void UDXDDepthStencilState::ReleaseDepthStencilState()
{
    
}
