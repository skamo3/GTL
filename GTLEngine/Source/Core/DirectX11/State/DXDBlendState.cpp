#include "pch.h"
#include "DXDBlendState.h"

UDXDBlendState::~UDXDBlendState()
{
    ReleaseBlendState();
}

HRESULT UDXDBlendState::CreateBlendState()
{


    return S_OK;
}

void UDXDBlendState::ReleaseBlendState()
{
    
}
