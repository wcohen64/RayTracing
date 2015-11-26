#pragma once
#include "Intersectable.h"

class Quadric : 
	public Intersectable
{
	float4x4 coeffs;

public:
	Quadric(Material* material) :
		Intersectable(material)
	{
		coeffs = float4x4();
		coeffs._00 = 1;
		coeffs._11 = 1;
		coeffs._22 = 1;
		coeffs._33 = -1;

	}


	Quadric* cylinder() {
		coeffs._11 = 0;
		return this;
	}

	Quadric* cone() {
		coeffs._11 = -1;
		coeffs._33 = 0;
		//coeffs._12 = 1;
		return this;
	}

	Quadric* paraboloid(){
		coeffs._11 = 0;
		coeffs._33 = 0;
		coeffs._13 = -1;
		return this;
	}

	Quadric* hyperboloid() {
		coeffs._11 = -1;
		return this;
	}

	Quadric* parallelPlanes() {
		coeffs._00 = 0;
		coeffs._11 = 1;
		coeffs._22 = 0;
		coeffs._33 = -1;
		return this;

	}

	Quadric* transform(float4x4 t) {
		float4x4 ti = t.invert();
		coeffs = ti * (coeffs * ti.transpose());
		return this;
	}

	Quadric* scale(float3 scale) {
		
		float4x4 ti = float4x4().scaling(scale);
		ti = ti.invert();
		coeffs = ti * (coeffs * ti.transpose());
		return this;
	}

	Quadric* translate(float3 offset) {
		
		float4x4 ti = float4x4().translation(offset);
		ti = ti.invert();
		coeffs = ti * (coeffs * ti.transpose());
		return this;
	}

	Quadric* rotate(const float3& axis, float angle) {

		float4x4 ti = float4x4().rotation(axis, angle);
		ti = ti.invert();
		coeffs = ti * (coeffs * ti.transpose());
		return this;
	}


	QuadraticRoots solveQuadratic(const Ray& ray)
	{
		float4 e = float4(ray.origin);
		float4 d = float4(ray.dir);
		d.w = 0;
		float a = d.dot(coeffs * d);
		float b = e.dot(coeffs * d) + d.dot(coeffs * e);
		float c = e.dot(coeffs * e);
		return QuadraticRoots(a, b, c);

	}

	float3 getNormalAt(float3 r)
	{
		float4 r4 = float4(r);
		float4 prenormal = (coeffs * r) + operator*(r, coeffs);
		return float3(prenormal.x, prenormal.y, prenormal.z).normalize();
	}
	Hit intersect(const Ray& ray)
	{
		float t = solveQuadratic(ray).getLesserPositive();

		Hit hit;
		hit.t = t;
		hit.material = material;
		hit.position = ray.origin + ray.dir * t;
		hit.normal = getNormalAt(hit.position);

		return hit;
	}

	bool contains(float3 r) {
		float4 rhomo(r);
		float hitTry = rhomo.dot(coeffs * rhomo);
		if (hitTry > 0){
			return false;
		}
		else {
			return true;
		}

	}

};