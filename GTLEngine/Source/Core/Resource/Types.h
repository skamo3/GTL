#pragma once

#include "Utils/Math/MathFwd.h"

enum class EPrimitiveType
{
    None,
    Line,
    Triangle,
    Rectangle,
    Sphere,
    Cube,
    Cylinder,
    Cone,

    Max,
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

//////////
// 
// Constant Buffers
// 
//////////
enum class EConstantBufferType
{
    None,
    ChangesOnResize,
    ChangesEveryFrame,
    ChangesEveryObject,

    Max,
};

struct FCbChangesOnResize
{
    FMatrix ProjectionMatrix;
};

struct FCbChangesEveryFrame
{
    FMatrix ViewMatrix;
};

struct FCbChangesEveryObject
{
    FMatrix WorldMatrix;
};

struct FCbLine
{
    FVector Position;
    float Padding;

    float R, G, B, A;
};