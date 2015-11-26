#pragma once
#include "Material.h"
#include "DarkMarble.h"
#include "Marble.h"
#include "Wood.h"

class ChessBoard :
	public Material
{
	Material* color1 = new Marble();
	Material* color2 = new DarkMarble();
	Material* color3 = new Wood();
	float boardStartX = -4;
	float boardStartZ = -4;
	float boardEndX = 3;
	float boardEndZ = 3;

public:
	ChessBoard() {}

	/*
	float3 getColor(float3 position) {
		int x = floor(position.x);
		int z = floor(position.z);

		if (x < boardStartX || x > boardEndX) {
			return frontColor;
		}
		else if (z < boardStartZ || z > boardEndZ) {
			return frontColor;
		}
		
		if (x % 2 == 0) {
			if (z % 2 == 0)
				return color1;
			else
				return color2;
		} else {
			if (z % 2 == 0)
				return color2;
			else
				return color1;
		}
			
		
	}
	*/
	float3 shade(float3 powerDensity, float3 lightDirection, float3 hitNormal, float3 viewDirection, float3 position) {
		int x = floor(position.x);
		int z = floor(position.z);

		if (x < boardStartX || x > boardEndX) {
			return color3->shade(powerDensity, lightDirection, hitNormal, viewDirection, position);
		}
		else if (z < boardStartZ || z > boardEndZ) {
			return color3->shade(powerDensity, lightDirection, hitNormal, viewDirection, position);
		}

		if (x % 2 == 0) {
			if (z % 2 == 0)
				return color1->shade(powerDensity, lightDirection, hitNormal, viewDirection, position);
			else
				return color2->shade(powerDensity, lightDirection, hitNormal, viewDirection, position);
		}
		else {
			if (z % 2 == 0)
				return color2->shade(powerDensity, lightDirection, hitNormal, viewDirection, position);
			else
				return color1->shade(powerDensity, lightDirection, hitNormal, viewDirection, position);
		}
		//return powerDensity * getColor(position) * (hitNormal.dot(lightDirection));
	}

	
};

