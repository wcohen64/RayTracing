#pragma once
#include "Material.h"
class Marble :
	public Material
{
public:
	float scale;
	float turbulence;
	float period;
	float sharpness;
public:
	Marble()
	{
		scale = 32;
		turbulence = 50;
		period = 32;
		sharpness = 1;
	}
	virtual float3 getColor(
		float3 position,
		float3 normal,
		float3 viewDir)
	{
		//return normal;
		float w = position.x * period + pow(snoise(position * scale), sharpness)*turbulence;
		w = pow(sin(w)*0.5 + 0.5, 4);
		return (float3(0, 0, 1) * w + float3(1, 1, 1) * (1 - w)) * normal.dot(viewDir);
	}

	float3 shade(float3 powerDensity, float3 lightDirection, float3 hitNormal, float3 viewDirection, float3 position) {
		float3 halfVector = (lightDirection + viewDirection).normalize();
		float temp = halfVector.dot(hitNormal);
		return powerDensity * getColor(position, hitNormal, viewDirection) * hitNormal.dot(lightDirection) + powerDensity * pow(temp, 21);
	}
};


