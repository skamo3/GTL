#include "pch.h"
#include "GizmoActor.h"

#include "GizmoArrowComponent.h"

AGizmoActor::AGizmoActor()
{
	ArrowComponent = AddComponent<UGizmoArrowComponent>(this);
}

void AGizmoActor::Tick(float TickTime)
{
}

void AGizmoActor::Destroy()
{
}
