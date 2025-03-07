#pragma once

class UDXDDepthStencilState
{
public:
	UDXDDepthStencilState() = default;
	~UDXDDepthStencilState();

	HRESULT CreateDepthStencilState();
	void ReleaseDepthStencilState();

private:
};

