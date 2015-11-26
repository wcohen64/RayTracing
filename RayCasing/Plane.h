#pragma once
#include "Intersectable.h"


class Plane : 
	public Intersectable
{
	float3 normal;
	float3 point;
public:
	Plane(const float3& normal, const float3& point, Material* material) :
		Intersectable(material),
		normal(normal),
		point(point)
	{}


	Hit intersect(const Ray& ray)
	{
		// This is a generic intersect that works for any shape with a quadratic equation. solveQuadratic should solve the proper equation (+ ray equation) for the shape, and getNormalAt should return the proper normal
		float t = (point - ray.origin).dot(normal) / (ray.dir.dot(normal));

		Hit hit;
		hit.t = t;
		hit.material = material;
		hit.position = ray.origin + ray.dir * t;
		hit.normal = normal;

		return hit;
	}
};
