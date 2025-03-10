#pragma once

enum class EPrimitiveType
{
    Line,
    Triangle,
    Rectangle,
    Sphere,
    Cube,
    NONE
};

struct FVertexSimple
{
    float X = 0.f, Y = 0.f, Z = 0.f;
    float R = 0.f, G = 0.f, B = 0.f, A = 1.f;
};

struct FVertexInfo
{
    uint NumVertices;
    ID3D11Buffer* VertexBuffer;
};