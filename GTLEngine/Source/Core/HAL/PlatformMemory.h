#pragma once

/**
 * 엔진의 Heap 메모리의 할당량을 추적하는 클래스
 *
 * @note new로 생성한 객체는 추적하지 않습니다.
 */
struct FPlatformMemory
{
private:
    static uint64 TotalAllocationBytes;
    static uint64 TotalAllocationCount;

   
    static void IncrementStats(size_t Size);

   
    static void DecrementStats(size_t Size);

public:
   
    static void* Malloc(size_t Size);

   
    static void* AlignedMalloc(size_t Size, size_t Alignment);

   
    static void Free(void* Address, size_t Size);

   
    static void AlignedFree(void* Address, size_t Size);

   
    static uint64 GetAllocationBytes();

   
    static uint64 GetAllocationCount();
};
