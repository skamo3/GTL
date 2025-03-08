#pragma once

class UDXDRasterizerState
{
public:
	UDXDRasterizerState() = default;
	~UDXDRasterizerState();

	HRESULT CreateRasterizerState(ComPtr<ID3D11Device> Device);
	void ReleaseRasterizerState();

	ComPtr<ID3D11RasterizerState> GetRasterizerState() const { return RasterizerState; }
private:
	ComPtr<ID3D11RasterizerState> RasterizerState;

};

