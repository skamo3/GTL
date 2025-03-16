#include "pch.h"
#include "Types.h"

FString GetPrimitiveTypeAsString(EPrimitiveType Type)
{
    switch (Type)
    {
    case EPrimitiveType::Line:
        return FString(TEXT("Line"));
    case EPrimitiveType::Triangle:
        return FString(TEXT("Triangle"));
    case EPrimitiveType::Sphere:
        return FString(TEXT("Sphere"));
    case EPrimitiveType::Cube:
        return FString(TEXT("Cube"));
    case EPrimitiveType::Cylinder:
        return FString(TEXT("Cylinder"));
    case EPrimitiveType::Cone:
        return FString(TEXT("Cone"));
    case EPrimitiveType::Grid:
        return FString(TEXT("Grid"));
    case EPrimitiveType::BoundingBox:
        return FString(TEXT("BoundingBox"));
    case EPrimitiveType::Max:
        return FString(TEXT("Max"));
    case EPrimitiveType::None:
    default:
        return FString(TEXT("None"));
    }
}
