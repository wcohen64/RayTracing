#pragma once
#include "Material.h"
class Wood :
	public Material
{
	float scale;
	float turbulence;
	float period;
	float sharpness;
public:
	Wood() 
	{
		scale = 16;
		turbulence = 500;
		period = 8;
		sharpness = 10;
	}
	virtual float3 getColor(
		float3 position,
		float3 normal,
		float3 viewDir)
	{
		//return normal;
		float w = position.x * period + pow(snoise(position * scale), sharpness)*turbulence + 10000.0;
		w -= int(w);
		return (float3(1, 0.3, 0) * w + float3(0.35, 0.1, 0.05) * (1 - w)) * normal.dot(viewDir);
	}

	float3 shade(float3 powerDensity, float3 lightDirection, float3 hitNormal, float3 viewDirection, float3 position) {
		return powerDensity * getColor(position, hitNormal, viewDirection) * (hitNormal.dot(lightDirection));
	}
};


