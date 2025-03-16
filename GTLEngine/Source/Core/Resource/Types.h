#pragma once

#include "Math/Vector.h"
#include "Math/Matrix.h"

enum class EPrimitiveType
{
    None,
    Line,
    Triangle,
    Sphere,
    Cube,
    Cylinder,
    Cone,
    Grid,
    BoundingBox,
    XArrow,
    YArrow,
    ZArrow,
    Max,
};

FString GetPrimitiveTypeAsString(enum class EPrimitiveType Type);

struct FVertexSimple
{
    float X = 0.f, Y = 0.f, Z = 0.f;
    float R = 0.f, G = 0.f, B = 0.f, A = 1.f;
};

struct FVertexUV
{
	float X = 0.f, Y = 0.f, Z = 0.f;
	float U = 0.f, V = 0.f;
};

struct FVertexInfo
{
    uint NumVertices;
    ID3D11Buffer* VertexBuffer;
};

struct FIndexInfo
{
    uint32 NumIndices;
    ID3D11Buffer* IndexBuffer;
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
    MVP,
    Max,
};

 struct alignas(16) FCbChangesOnResize
{
    FMatrix ProjectionMatrix;
};


struct alignas(16) FCbChangesEveryFrame
{
    FMatrix ViewMatrix;
};

struct alignas(16)  FCbChangesEveryObject
{
    FMatrix WorldMatrix;
};

struct alignas(16) FMVP
{
    FMatrix MVP;
};

struct FCbLine
{
    FVector Position;
    float R, G, B, A;
};

struct FRay {
    FVector Origin;
    FVector Direction;
    FRay(FVector origin, FVector direction) : Origin(origin), Direction(direction) {};
    inline FVector GetNormalizedDirection() const { return Direction.GetSafeNormal(); }
};

struct FAABB {
    FVector min;
    FVector max;
    FAABB(FVector min, FVector max) : min(min), max(max) {};
    FVector GetGap() { return max - min; }
};