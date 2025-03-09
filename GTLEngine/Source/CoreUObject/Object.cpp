#include "pch.h"
#include "Object.h"

#include "Engine/Engine.h"

UObject::UObject()
{
	UUID = UEngineStatics::GenUUID();
	InternalIndex = 0;
	NamePrivate = "";
}

UObject::~UObject()
{
}

void* UObject::operator new(size_t size)
{
	void* ptr = ::operator new(size);
	UEngine::GetEngine().AddTotalAllocationBytes(static_cast<uint>(size));
	UEngine::GetEngine().AddTotalAllocationCount(1);
	return ptr;
}

void* UObject::operator new[](size_t size)
{
	void* ptr = ::operator new[](size);
	UEngine::GetEngine().AddTotalAllocationBytes(static_cast<uint>(size));

	// TODO: 하위 객체일 때도 정확한 크기로 들어가고 있는지 메모리 확장/축소될 때 크기확인 필요.
	UEngine::GetEngine().AddTotalAllocationCount(static_cast<uint32>(size / sizeof(UObject)));
	return ptr;
}

void UObject::operator delete(void* ptr)
{
	if (ptr == nullptr)
		return;
	size_t size = _msize(ptr);
	UEngine::GetEngine().RemoveTotalAllocationBytes(static_cast<uint>(size));
	UEngine::GetEngine().RemoveTotalAllocationCount(1);
	::operator delete(ptr);
}

void UObject::operator delete[](void* ptr)
{
	if (ptr == nullptr)
		return;
	size_t size = _msize(ptr);
	UEngine::GetEngine().RemoveTotalAllocationBytes(static_cast<uint>(size));
	UEngine::GetEngine().RemoveTotalAllocationCount(static_cast<uint32>(size / sizeof(UObject)));
	::operator delete[](ptr);
}
