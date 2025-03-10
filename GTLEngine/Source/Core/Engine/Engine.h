#pragma once

#include "Math/Math.h"

class UDirectXHandle;
class UResourceManager;
class UWorld;
class UTimeManager;
class UInputManager;
class UGizmo;
class UObject;
class UAssetManager;

class UEngineStatics
{
public:
    static uint32 GenUUID()
    {
        return NextUUID++;
    }

private:
    static uint32 NextUUID;
};

class UEngine
{

public:
    static UEngine& GetEngine()
    {
        static UEngine Engine;
        return Engine;
    }

    bool InitEngine(const FWindowInfo& InWindowInfo);
	void Tick();
    void Render();
	void ClearEngine();

    HRESULT AddAllPrimitiveVertexBuffers();

    // Getter
    UDirectXHandle* GetDirectX11Handle() const { return DirectX11Handle; }
    UResourceManager* GetResourceManager() const { return ResourceManager; }
    UWorld* GetWorld() const { return World; }
    UInputManager* GetInputManager() const { return InputManager; }
	UAssetManager* GetAssetManager() const { return AssetManager; }

private:
    UEngine() = default;
    ~UEngine() = default;
    UEngine(const UEngine&) = delete;
    UEngine& operator=(const UEngine&) = delete;
    UEngine(UEngine&&) = delete;
    UEngine& operator=(UEngine&&) = delete;

private:
	UDirectXHandle* DirectX11Handle;
	UResourceManager* ResourceManager;
    UWorld* World;
    UTimeManager* TimeManager;
    UInputManager* InputManager;
    UGizmo* Gizmo;

    UObject* SelectedObject;

    TArray<TPair<FVector, FVector>> Lines;

	UAssetManager* AssetManager;

public:
    const FWindowInfo& GetWindowInfo() const { return WindowInfo; }

private:
    FWindowInfo WindowInfo;

public:
    uint32 GetTotalAllocationBytes() const { return TotalAllocationBytes; }
    uint32 GetTotalAllocationCount() const { return TotalAllocationCount; }

    void AddTotalAllocationBytes(uint32 Bytes);
    void AddTotalAllocationCount(uint32 Count);

    void RemoveTotalAllocationBytes(uint32 Bytes);
    void RemoveTotalAllocationCount(uint32 Count);

private:
    uint32 TotalAllocationBytes;
    uint32 TotalAllocationCount;

};

