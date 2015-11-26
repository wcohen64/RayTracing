#pragma once
#include "float3.h"
#include "Material.h"

class Hit
{
public:
	Hit()
	{
		t = -1;
	}
	float t;				//< Ray paramter at intersection. Negative means no valid intersection.
	float3 position;		//< Intersection coordinates.
	float3 normal;			//< Surface normal at intersection.
	Material* material;		//< Material of intersected surface.
};

