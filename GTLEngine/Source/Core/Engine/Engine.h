#pragma once

#include "Math/Vector.h"

class UDirectXHandle;
class UResourceManager;
class UWorld;
class UTimeManager;
class UInputManager;
class UGizmoManager;
class UObject;
class UAssetManager;
class UUIManager;

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

private:
    UEngine() = default;
    ~UEngine() = default;
    UEngine(const UEngine&) = delete;
    UEngine& operator=(const UEngine&) = delete;
    UEngine(UEngine&&) = delete;
    UEngine& operator=(UEngine&&) = delete;

public:
    // Getter
    UDirectXHandle* GetDirectX11Handle() const { return DirectX11Handle; }
    UResourceManager* GetResourceManager() const { return ResourceManager; }
    UWorld* GetWorld() const { return World; }
	UTimeManager* GetTimeManager() const { return TimeManager; }
    UInputManager* GetInputManager() const { return InputManager; }
    UUIManager* GetUIManager() const { return UIManager; }
    UAssetManager* GetAssetManager() const { return AssetManager; }
	UGizmoManager* GetGizmo() const { return GizmoManager; }
    


private:
	UDirectXHandle* DirectX11Handle;
	UResourceManager* ResourceManager;
    UWorld* World;
    UTimeManager* TimeManager;
    UInputManager* InputManager;
    UUIManager* UIManager;
    UGizmoManager* GizmoManager;

	UAssetManager* AssetManager;

public:
    const FWindowInfo& GetWindowInfo() const { return WindowInfo; }

private:
    FWindowInfo WindowInfo;

public:
	float GetFPS() const { return FPS; }
	void SetFPS(float InFPS) { FPS = InFPS; }

private:
    float FPS;

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

