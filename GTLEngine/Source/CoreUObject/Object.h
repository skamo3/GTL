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
	uint32 UUID;
	uint32 InternalIndex; // Index of GUObjectArray
};

//TArray<UObject*> GUObjectArray;