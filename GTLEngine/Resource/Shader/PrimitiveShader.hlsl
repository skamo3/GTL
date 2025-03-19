#include "MVPShader.hlsli"

struct VS_INPUT
{
    float4 Position : POSITION; // Input position from vertex buffer
    float4 Color : COLOR; // Input color from vertex buffer
};

struct PS_INPUT
{
    float4 Position : SV_POSITION; // Transformed position to pass to the pixel shader
    float4 Color : COLOR; // Color to pass to the pixel shader
};

PS_INPUT mainVS(VS_INPUT Input)
{
    Input.Position.w = 1.f;
    
    PS_INPUT Output = (PS_INPUT) 0.0f;
    // Output.Position = mul(Input.Position, MVP); // 오브젝트 스페이스 -> NDC
    
    Output.Position = Input.Position;
    Output.Position = mul(Output.Position, WorldMatrix); // 오브젝트 스페이스 -> 월드 스페이스
    Output.Position = mul(Output.Position, ViewMatrix); // 월드 스페이스 -> 뷰 스페이스
    Output.Position = mul(Output.Position, ProjectionMatrix); // 뷰 스페이스 -> NDC
    
    Output.Color = Input.Color;
    
    return Output;
}

float4 mainPS(PS_INPUT Input) : SV_TARGET
{
    // Output the color directly
    return Input.Color;
}