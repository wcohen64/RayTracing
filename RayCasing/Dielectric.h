#pragma once
#include "Material.h"

class Dielectric : 
	public Material 
{
	
	float  refractiveIndex;
	float  r0;
public:
	Dielectric(float refractiveIndex) : refractiveIndex(refractiveIndex) {
		r0 = (refractiveIndex - 1)*(refractiveIndex - 1)
			/ (refractiveIndex + 1)*(refractiveIndex + 1);
	}
	struct Event{
		float3 reflectionDir;
		float3 refractionDir;
		float reflectance;
		float transmittance;
	};
	Event evaluateEvent(float3 inDir, float3 normal) {
		Event e;
		float cosa = -normal.dot(inDir);
		float3 perp = -normal * cosa;
		float3 parallel = inDir - perp;
		e.reflectionDir = parallel - perp;

		float ri = refractiveIndex;
		if (cosa < 0) { cosa = -cosa; normal = -normal; ri = 1 / ri; }
		float disc = 1 - (1 - cosa * cosa) / ri / ri;
		if (disc < 0) e.reflectance = 1;
		else {
			float cosb = (disc < 0) ? 0 : sqrt(disc);
			e.refractionDir = parallel / ri - normal * cosb;
			e.reflectance = r0 + (1 - r0) * pow(1 - cosa, 5);
		}
		e.transmittance = 1 - e.reflectance;
		return e;
	}

	virtual float3 shade(float3 powerDensity, float3 lightDirection, float3 hitNormal, float3 viewDirection, float3 position) {
		return float3(0, 0, 0);
		float3 halfVector = (lightDirection + viewDirection).normalize();
		float temp = halfVector.dot(hitNormal);
		return powerDensity * pow(temp, 21);
	}
};
