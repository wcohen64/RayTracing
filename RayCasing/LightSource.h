#pragma once
#include "float3.h"


class LightSource
{
protected:
	float3 powerDensity;

public:
	LightSource(float3 powerDensity) : powerDensity(powerDensity) {}
	virtual float3 getPowerDensityAt(float3 x) = 0;
	virtual float3 getLightDirAt(float3 x) = 0;
	virtual float  getDistanceFrom(float3 x) = 0;
};


