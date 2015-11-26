#pragma once
#include "Material.h"

class Metal :
	public Material
{
	float3 r0;

public:
	Metal(float3  refractiveIndex, float3  extinctionCoefficient)
	{
		float3 rim1 = refractiveIndex - float3(1, 1, 1);
		float3 rip1 = refractiveIndex + float3(1, 1, 1);
		float3 k2 = extinctionCoefficient * extinctionCoefficient;
		r0 = (rim1*rim1 + k2) / (rip1*rip1 + k2);
	}

	struct Event{
		float3 reflectionDir;
		float3 reflectance;
	};
	
	Event evaluateEvent(float3 inDir, float3 normal) {
		Event e;
		float cosa = -normal.dot(inDir);
		float3 perp = -normal * cosa;
		float3 parallel = inDir - perp;
		e.reflectionDir = parallel - perp;
		e.reflectance = r0 + (float3(1, 1, 1) - r0) * pow(1 - cosa, 5);
		return e;
	}

	virtual float3 shade(float3 powerDensity, float3 lightDirection, float3 hitNormal, float3 viewDirection, float3 position) {
		float3 halfVector = (lightDirection + viewDirection).normalize();
		float temp = halfVector.dot(hitNormal);
		return powerDensity * pow(temp, 21);
	}

};
