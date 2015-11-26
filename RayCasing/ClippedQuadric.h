#pragma once
#include "Intersectable.h"
#include "Quadric.h"


class ClippedQuadric : public Intersectable {

	Quadric* shape;
	Quadric* clipper;

public:
	ClippedQuadric(Quadric* shape, Quadric* clipper, Material* material) :
		shape(shape),
		clipper(clipper),
		Intersectable(material)
	{
	}

	ClippedQuadric* translate(float3 offset) {
		shape = shape->translate(offset);
		clipper = clipper->translate(offset);
		return this;
	}

	Hit intersect(const Ray& ray)
	{
		QuadraticRoots roots = shape->solveQuadratic(ray);

		Hit hit1;
		hit1.t = roots.t1;
		hit1.material = material;
		hit1.position = ray.origin + ray.dir * roots.t1;
		hit1.normal = shape->getNormalAt(hit1.position);

		Hit hit2;
		hit2.t = roots.t2;
		hit2.material = material;
		hit2.position = ray.origin + ray.dir * roots.t2;
		hit2.normal = shape->getNormalAt(hit2.position);

		if (!clipper->contains(hit1.position)) {
			hit1.t = -1;
		}
		if (!clipper->contains(hit2.position)) {
			hit2.t = -1;
		}

		if (hit1.t < 0) {
			return hit2;
		}
		if (hit2.t < 0) {
			return hit1;
		}
		if (hit1.t < hit2.t)
			return hit1;
		else
			return hit2;

	}

};