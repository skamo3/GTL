#pragma once
#include "EnginePch.h"
#include "Core/Resource/Types.h"

class IClickable {
private:
	static TArray<IClickable*> ClickableList;
	uint32 InternalIndex;
public:
	inline static TArray<IClickable*> GetClickableList() { return ClickableList; };
	IClickable() {
		InternalIndex = static_cast<uint32>(ClickableList.size());
		ClickableList.push_back(this);
	}
	virtual ~IClickable() {
		ClickableList[InternalIndex] = nullptr;
	}
	virtual void OnRelease() abstract;
	virtual void OnClick() abstract;
	virtual bool IsClicked(FRay ray, float maxDistance, FVector& hitpoint) abstract;
};

class IDragable {
private:
	static TArray<IDragable*> DragableList;
	uint32 InternalIndex;
public:
	inline static TArray<IDragable*> GetDragableList() { return DragableList; };
	IDragable() {
		InternalIndex = static_cast<uint32>(DragableList.size());
		DragableList.push_back(this);
	}
	virtual ~IDragable() {
		DragableList[InternalIndex] = nullptr;
	}
	
	virtual void OnDragStart(int mx, int my) abstract;
	virtual void OnDragTick(int dmx, int dmy) abstract;
	virtual void OnDragEnd(int mx, int my) abstract;
};