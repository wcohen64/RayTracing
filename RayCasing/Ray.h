#pragma once
#include "float3.h"

class Ray
{
public:
	float3 origin;
	float3 dir;
	Ray(float3 o, float3 d)
	{
		origin = o;
		dir = d;
	}
};