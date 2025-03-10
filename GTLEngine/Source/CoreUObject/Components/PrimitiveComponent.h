#pragma once

#include "SceneComponent.h"
#include "Core/Resource/VertexTypes.h"

class UPrimitiveComponent : public USceneComponent
{
public:
	virtual void Tick(float TickTime) override;
	virtual void Destroy() override;


public:
	const TArray<FVertexSimple*> GetVertices() const { return Vertices; }
private:
	EPrimitiveType PrimitiveType;
	TArray<FVertexSimple*> Vertices;


};