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
	return nullptr;
}

void* UObject::operator new[](size_t size)
{
	return nullptr;
}

void UObject::operator delete(void* ptr)
{
}

void UObject::operator delete[](void* ptr)
{
}
