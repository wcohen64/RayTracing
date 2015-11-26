#pragma once
#include "float3.h"
#include "float2.h"

class Camera
{
	float3 eye;		//< world space camera position
	float3 lookAt;	//< center of window in world space
	float3 right;	//< vector from window center to window right-mid (in world space)
	float3 up;		//< vector from window center to window top-mid (in world space)

public:
	Camera()
	{
		//eye = float3(0, 0, 3);
		eye = float3(3, 0, 3);
		//lookAt = float3(0, 0, 2);
		lookAt = float3(1, -1, 1);
		//right = float3(1, 0, 3);
		right = float3(1, 0, 0);
		//up = float3(0, 1, 0);
		up = float3(0, 1, 0);

		float3 direction = (lookAt - eye).normalize();
		right = up.cross(direction).normalize();
		up = (direction).cross(right).normalize();

	}
	float3 getEye()
	{
		return eye;
	}

	float3 rayDirFromNdc(const float2 ndc) {
		return (lookAt - eye
			+ right * ndc.x
			+ up    * ndc.y
			).normalize();
	}
};
