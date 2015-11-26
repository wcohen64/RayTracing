#pragma once
#include "Material.h"

class BlinnPhong :
	public Material
{
public:
	BlinnPhong() {
		frontColor = float3(.95, 1, .98);
	}

	float3 shade(float3 powerDensity, float3 lightDirection, float3 hitNormal, float3 viewDirection, float3 position) {
		float3 halfVector = (lightDirection + viewDirection).normalize();
		float temp = halfVector.dot(hitNormal);
		return frontColor * hitNormal.dot(lightDirection) + powerDensity * pow(temp, 21);
	}

};

