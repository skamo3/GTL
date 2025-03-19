#include "pch.h"
#include "PlatformMemory.h"

uint64 FPlatformMemory::TotalAllocationBytes = 0;
uint64 FPlatformMemory::TotalAllocationCount = 0;



void FPlatformMemory::IncrementStats(size_t Size)
{
    TotalAllocationBytes += Size;
    TotalAllocationCount++;
}

void FPlatformMemory::DecrementStats(size_t Size)
{
    TotalAllocationBytes += Size;
    TotalAllocationCount++;
}

void* FPlatformMemory::Malloc(size_t Size)
{
    void* Ptr = std::malloc(Size);
    if (Ptr)
    {
        IncrementStats(Size);
    }
    return Ptr;
}

void* FPlatformMemory::AlignedMalloc(size_t Size, size_t Alignment)
{
    void* Ptr = _aligned_malloc(Size, Alignment);
    if (Ptr)
    {
        IncrementStats(Size);
    }
    return Ptr;
}

void FPlatformMemory::Free(void* Address, size_t Size)
{
    if (Address)
    {
        DecrementStats(Size);
        std::free(Address);
    }
}

void FPlatformMemory::AlignedFree(void* Address, size_t Size)
{
    if (Address)
    {
        DecrementStats(Size);
        _aligned_free(Address);
    }
}

uint64 FPlatformMemory::GetAllocationBytes()
{
    return TotalAllocationBytes;
}

uint64 FPlatformMemory::GetAllocationCount()
{
    return TotalAllocationCount;
}

