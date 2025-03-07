#pragma once

class UDXDDevice;

class UDXDRasterizerState
{
public:
	UDXDRasterizerState() = default;
	~UDXDRasterizerState();

	HRESULT CreateRasterizerState(shared_ptr<UDXDDevice> Device);
	void ReleaseRasterizerState();

	ComPtr<ID3D11RasterizerState> GetRasterizerState() const { return RasterizerState; }
private:
	ComPtr<ID3D11RasterizerState> RasterizerState;

};

