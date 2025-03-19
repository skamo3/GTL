#pragma once

class UDXDDepthStencilState
{
public:
	UDXDDepthStencilState() = default;
	~UDXDDepthStencilState();

	HRESULT CreateDepthStencilState(ComPtr<ID3D11Device> Device);
	void ReleaseDepthStencilState();

	TArray<ID3D11DepthStencilState*> GetDepthStencilStates() const { return DepthStencilStates; }
private:
	TArray<ID3D11DepthStencilState*> DepthStencilStates;
};