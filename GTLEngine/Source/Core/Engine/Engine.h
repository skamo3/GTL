#pragma once

class UDirectXHandle;
class UResourceManager;
class UWorld;

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
	void Update();
    void Render();
	void ClearEngine();

private:
    UEngine() = default;
    ~UEngine() = default;
    UEngine(const UEngine&) = delete;
    UEngine& operator=(const UEngine&) = delete;
    UEngine(UEngine&&) = delete;
    UEngine& operator=(UEngine&&) = delete;

private:
	UDirectXHandle* DirectX11Handle;
	shared_ptr<UResourceManager> ResourceManager;
    shared_ptr<UWorld> World;


public:
    void AddTotalAllocationBytes(uint32 NewBytes);
    void AddTotalAllocationCount(uint32 Count);

    void RemoveTotalAllocationBytes(uint32 NewBytes);
    void RemoveTotalAllocationCount(uint32 Count);

private:
    uint32 TotalAllocationBytes;
    uint32 TotalAllocationCount;

};

