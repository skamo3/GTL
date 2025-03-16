#include "pch.h"
#include "GizmoActor.h"

#include "GizmoArrow.h"

AGizmoActor::AGizmoActor()
{
	//ArrowComponent = AddComponent<UGizmoArrow>(this);
	//ArrowComponent->SetupAttachment(RootComponent);
}

void AGizmoActor::Tick(float TickTime)
{
}

void AGizmoActor::Destroy()
{
}
