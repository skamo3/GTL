#pragma once

class UObject
{
public:
	UObject();
	~UObject();

	void* operator new(size_t size);
	void* operator new[](size_t size);
	void operator delete(void* ptr);
	void operator delete[](void* ptr);

public:
	virtual void Tick(float TickTime) = 0;
	virtual void Destroy() = 0;

public:
	
	std::wstring GetName() const { return NamePrivate; }
	void SetName(const std::wstring& Name) { NamePrivate = Name; }
	inline const uint32 GetUUID() const { return UUID; }
private:
	// Name of this object.
	std::wstring NamePrivate;


private:
	uint32 UUID;
	uint32 InternalIndex; // Index of GUObjectArray

private:
	UObject(const UObject&) = delete;
	UObject(const UObject&&) = delete;
	UObject& operator=(const UObject&) = delete;
	UObject& operator=(const UObject&&) = delete;

};

extern TArray<UObject*> GUObjectArray;