#pragma once

class UDirectXHandle;
class UResourceManager;

class UEngine
{

public:
    static UEngine& GetEngine()
    {
        static UEngine Engine;
        return Engine;
    }

    void InitEngine();

private:
    UEngine() = default;
    ~UEngine() = default;
    UEngine(const UEngine&) = delete;
    UEngine& operator=(const UEngine&) = delete;
    UEngine(UEngine&&) = delete;
    UEngine& operator=(UEngine&&) = delete;
	

private:
	shared_ptr<UDirectXHandle> DirectX11Handle;
	shared_ptr<UResourceManager> ResourceManager;
};

