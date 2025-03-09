#pragma once

class UDirectXHandle;
class UResourceManager;
class UWorld;
class UInputManager;

class ACamera;

class UEngineStatics
{
public:
    UEngineStatics();

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

    bool InitEngine(HWND hWnd);
	void Tick();
    void Render();
	void ClearEngine();

    // Getter
    UDirectXHandle* GetDirectX11Handle() const { return DirectX11Handle; }
    UResourceManager* GetResourceManager() const { return ResourceManager.get(); }
    UWorld* GetWorld() const { return World.get(); }
    UInputManager* GetInputManager() const { return InputManager; }

    uint32 GetTotalAllocationBytes() const { return TotalAllocationBytes; }
    uint32 GetTotalAllocationCount() const { return TotalAllocationCount; }

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

    ACamera* MainCamera;
    UInputManager* InputManager;

public:
    void AddTotalAllocationBytes(uint32 NewBytes);
    void AddTotalAllocationCount(uint32 Count);

    void RemoveTotalAllocationBytes(uint32 NewBytes);
    void RemoveTotalAllocationCount(uint32 Count);

private:
    uint32 TotalAllocationBytes;
    uint32 TotalAllocationCount;

};

