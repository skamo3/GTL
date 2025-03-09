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
	string GetName() const { return NamePrivate; }

protected:// 자기 자신만 스스로를 바꿀 수 있도록.
	void SetName(const string& NewName) { NamePrivate = NewName; } 

private:
	// Name of this object.
	string NamePrivate;


public:
	uint32 UUID;
	uint32 InternalIndex; // Index of GUObjectArray

private:
	UObject(const UObject&) = delete;
	UObject(const UObject&&) = delete;
	UObject& operator=(const UObject&) = delete;
	UObject& operator=(const UObject&&) = delete;

};

//TArray<UObject*> GUObjectArray;