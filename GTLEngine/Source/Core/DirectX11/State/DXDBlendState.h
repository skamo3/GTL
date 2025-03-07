#pragma once

class UDXDBlendState
{
public:
	UDXDBlendState() = default;
	~UDXDBlendState();

	HRESULT CreateBlendState();
	void ReleaseBlendState();

private:
};

