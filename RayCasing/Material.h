#pragma once
#include "float3.h"

class Material
{
protected:
	float3 frontColor = float3(1,0,0);

public:
	Material() 
	{}

	virtual float3 shade(float3 powerDensity, float3 lightDirection, float3 hitNormal, float3 viewDirection, float3 position) = 0;
	
	float3 snoiseGrad(float3 r)
	{
		unsigned int x = 0x0625DF73;
		unsigned int y = 0xD1B84B45;
		unsigned int z = 0x152AD8D0;
		float3 f = float3(0, 0, 0);
		for (int i = 0; i<32; i++)
		{
			float3 s(x / (float)0xffffffff,
				y / (float)0xffffffff,
				z / (float)0xffffffff);
			f += s * cos(s.dot(r));
			x = x << 1 | x >> 31;
			y = y << 1 | y >> 31;
			z = z << 1 | z >> 31;
		}
		return f * (1.0 / 64.0);
	}

	float snoise(float3 r) {
		unsigned int x = 0x0625DF73;
		unsigned int y = 0xD1B84B45;
		unsigned int z = 0x152AD8D0;
		float f = 0;
		for (int i = 0; i<32; i++) {
			float3 s(x / (float)0xffffffff,
				y / (float)0xffffffff,
				z / (float)0xffffffff);
			f += sin(s.dot(r));
			x = x << 1 | x >> 31;
			y = y << 1 | y >> 31;
			z = z << 1 | z >> 31;
		}
		return f / 64.0 + 0.5;
	}

	
};