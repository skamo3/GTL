#pragma once
#include "EnginePch.h"
#include "Core/Resource/Types.h"

class IClickable {
private:
	static TList<IClickable*> ClickableList;
	uint32 _InternalIndex;
public:
	inline static TList<IClickable*> GetClickableList() { return ClickableList; };
	IClickable() {
		_InternalIndex = static_cast<uint32>(ClickableList.size());
		ClickableList.push_back(this);
	}
	virtual ~IClickable() {
		ClickableList.remove(this);
	}
	virtual void OnRelease(int mx, int my) abstract;
	virtual void OnClick(int mx, int my) abstract;
	virtual bool IsClicked(FRay ray, float maxDistance, FVector& hitpoint) abstract;
};

class IDragable: public IClickable {
private:
	static TList<IDragable*> DragableList;
	uint32 _InternalIndex;
public:
	inline static TList<IDragable*> GetDragableList() { return DragableList; };
	IDragable() {
		_InternalIndex = static_cast<uint32>(DragableList.size());
		DragableList.push_back(this);
	}
	virtual ~IDragable() {
		DragableList.remove(nullptr);
	}
	virtual void OnDragTick(int dmx, int dmy) abstract;
};