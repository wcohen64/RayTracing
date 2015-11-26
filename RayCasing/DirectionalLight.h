#pragma once
#include "LightSource.h"
#include "float3.h"

class DirectionalLight :
	public LightSource
{
	float3 direction;

public:
	DirectionalLight(float3 powerDensity, float3 direction) : 
		LightSource(powerDensity),
		direction(direction)
	{}

	float3 getPowerDensityAt(float3 x) {
		return powerDensity;
	}

	float3 getLightDirAt(float3 x) {
		return direction;
	}

	float  getDistanceFrom(float3 x) {
		return 1000000;
	}

	

};

