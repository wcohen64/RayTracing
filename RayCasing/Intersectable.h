#pragma once
#include "Material.h"
#include "Hit.h"
#include "Ray.h"
#include "float4x4.h"
#include "QuadraticRoots.h"


class Intersectable
{
protected:
	Material* material;
public:
	Intersectable(Material* material) :material(material) {}
	virtual Hit intersect(const Ray& ray) = 0;
};
