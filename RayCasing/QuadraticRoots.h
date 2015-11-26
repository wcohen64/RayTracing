#pragma once
#include <math.h>

class QuadraticRoots
{
public:
	float t1;
	float t2;
	// Solves the quadratic a*a*t + b*t + c = 0 using the Quadratic Formula [-b +- sqrt(b^2-4ac)] / 2a, and set members t1 and t2 to store the roots.
	QuadraticRoots(float a, float b, float c)
	{
		float discr = b * b - 4.0 * a * c;
		if (discr < 0) // no roots
		{
			t1 = -1;
			t2 = -1;
			return;
		}
		float sqrt_discr = sqrt(discr);
		t1 = (-b + sqrt_discr) / 2.0 / a;
		t2 = (-b - sqrt_discr) / 2.0 / a;
	}
	// Returns the lesser of the positive solutions, or a negative value if there was no positive solution.
	float getLesserPositive()
	{
		return (0 < t1 && t1 < t2 || t2 < 0) ? t1 : t2;
	}
};