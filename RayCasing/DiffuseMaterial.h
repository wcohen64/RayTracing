#pragma once
#include "Material.h"

class DiffuseMaterial :
	public Material
{
public:
	DiffuseMaterial() {}

	float3 shade(float3 powerDensity, float3 lightDirection, float3 hitNormal, float3 viewDirection, float3 position) {
		return powerDensity * frontColor * (hitNormal.dot(lightDirection));
	}
	
};

