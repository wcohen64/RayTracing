#pragma once
#include "Material.h"

class RoughDiffuse :
	public Material
{
public:
	RoughDiffuse() {
		frontColor = float3(0, 0, 0);
	}
	
	float3 shade(float3 powerDensity, float3 lightDirection, float3 hitNormal, float3 viewDirection, float3 position) {
		hitNormal = hitNormal + snoiseGrad(hitNormal * 100);
		float3 halfVector = (lightDirection + viewDirection).normalize();
		float temp = halfVector.dot(hitNormal);
		return frontColor * hitNormal.dot(lightDirection) + powerDensity * pow(temp, 21);
	}
};

