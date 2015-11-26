#pragma once
#include <math.h>
#include "LightSource.h"
#include "float3.h"



class PointLight :
	public LightSource
{
	float3 position;

public:
	PointLight(float3 powerDensity, float3 position) :
		LightSource(powerDensity),
		position(position) 
	{}

	float3 getPowerDensityAt(float3 x) {
		return powerDensity * (1.0 / (float)(4.0 * 3.14159 * (position - x).norm2()));
	}

	float3 getLightDirAt(float3 x) {
		return (position - x).normalize();
	}

	float  getDistanceFrom(float3 x) {
		return (position - x).norm();
	}

};

