#pragma once
#include <vector>
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Material.h" 
#include "Hit.h"
#include "DiffuseMaterial.h"
#include "RoughDiffuse.h"
#include "BlinnPhong.h"
#include "ChessBoard.h"
#include "Wood.h"
#include "Marble.h"
#include "DarkMarble.h"
#include "Metal.h"
#include "Dielectric.h"
#include "Camera.h"
#include "Intersectable.h"
#include "Plane.h"
#include "Quadric.h"
#include "ClippedQuadric.h"




class Scene
{
	Camera camera;
	std::vector<Intersectable*> objects;
	std::vector<Material*> materials;
	std::vector<LightSource*> lights;
	int maxDepth = 2;
public:
	Scene()
	{
		Material* gold = new Metal(float3(.21, .485, 1.29), float3(3.13, 2.23, 1.76));
		Material* glass = new Dielectric(.9);

		lights.push_back(new PointLight(float3(500, 500, 500), float3(2, 3, -2)));
		lights.push_back(new PointLight(float3(300, 300, 300), float3(-2, 3, 3)));
		materials.push_back(new BlinnPhong());
		materials.push_back(new RoughDiffuse());
		materials.push_back(new ChessBoard());
		materials.push_back(new Wood());
		materials.push_back(new Marble());
		materials.push_back(gold);
		materials.push_back(glass);
		
		//////////////////////////////////////////////////////////
		//PAWN
		float3 pawnOffset = float3(1.5, -1.6, 0.3);
		Material* pawnMat = materials[0];
		
		Quadric* pawnStem(new Quadric(pawnMat));
		pawnStem->cone();
		pawnStem->scale(float3(.1, 1, .1));
		pawnStem->translate(float3(0, 1.3, 0) + pawnOffset);

		Quadric* pawnStemClipper(new Quadric(pawnMat));
		pawnStemClipper->parallelPlanes();
		pawnStemClipper->scale(float3(1, .3, 1));
		pawnStemClipper->translate(float3(0, 0, 0) + pawnOffset);

		Quadric* pawnTop(new Quadric(pawnMat));
		pawnTop->scale(float3(0.15, 0.15, 0.15));
		pawnTop->translate(float3(0, .3, 0) + pawnOffset);

		Quadric* pawnBase(new Quadric(pawnMat));
		pawnBase->scale(float3(.2, .08, .2));
		pawnBase->translate(float3(0, -.3, 0) + pawnOffset);

		objects.push_back(pawnBase);
		objects.push_back(pawnTop);
		objects.push_back(new ClippedQuadric(
			pawnStem,
			pawnStemClipper,
			pawnMat));

		
		//////////////////////////////////////////////////////////
		//Bishop
		float3 bishopOffset = float3(0, -1.6, 1);
		Material* bishopMat = materials[1];
		
		Quadric* bishopBase(new Quadric(bishopMat));
		bishopBase->scale(float3(.2, .1, .2));
		bishopBase->translate(float3(0, -.35, 0) + bishopOffset);

		Quadric* bishopBib(new Quadric(bishopMat));
		bishopBib->scale(float3(.17, .04, .17));
		bishopBib->translate(float3(0, .35, 0) + bishopOffset);

		Quadric* bishopStem(new Quadric(bishopMat));
		bishopStem->cylinder();
		bishopStem->scale(float3(0.11, 1, .11));
		bishopStem->translate(float3(0, .5, 0) + bishopOffset);

		Quadric* bishopStemClipper(new Quadric(bishopMat));
		bishopStemClipper->parallelPlanes();
		bishopStemClipper->scale(float3(1, .35, 1));
		bishopStemClipper->translate(float3(0, 0, 0) + bishopOffset);

		Quadric* bishopHeadBase(new Quadric(bishopMat));
		bishopHeadBase->scale(float3(.11, .11, .11));
		bishopHeadBase->translate(float3(0, .4, 0) + bishopOffset);

		Quadric* bishopHeadPoint(new Quadric(bishopMat));
		bishopHeadPoint->cone();
		bishopHeadPoint->scale(float3(.49, 1, .49));
		bishopHeadPoint->translate(float3(0, .65, 0) + bishopOffset);

		Quadric* bishopHeadClipper(new Quadric(bishopMat));
		bishopHeadClipper->parallelPlanes();
		bishopHeadClipper->scale(float3(1, .1, 1));
		bishopHeadClipper->translate(float3(0, .55, 0) + bishopOffset);

		Quadric* bishopTip(new Quadric(bishopMat));
		bishopTip->scale(float3(.03, .03, .03));
		bishopTip->translate(float3(0, .65, 0) + bishopOffset);

		objects.push_back(bishopBase);
		objects.push_back(bishopBib);
		objects.push_back(bishopHeadBase);
		objects.push_back(bishopTip);
		objects.push_back(new ClippedQuadric(
			bishopStem,
			bishopStemClipper,
			bishopMat));
		objects.push_back(new ClippedQuadric(
			bishopHeadPoint,
			bishopHeadClipper,
			bishopMat));


		//////////////////////////////////////////////////////////
		//Queen
		
		float3 queenOffset = float3(-.5, -1.55, 0);
		Material* queenMat = materials[5];

		Quadric* queenBase(new Quadric(queenMat));
		queenBase->scale(float3(.25, .1, .25));
		queenBase->translate(float3(0, -.35, 0) + queenOffset);

		Quadric* queenBib1(new Quadric(queenMat));
		queenBib1->scale(float3(.13, .03, .13));
		queenBib1->translate(float3(0, .7, 0) + queenOffset);

		Quadric* queenBib2(new Quadric(queenMat));
		queenBib2->scale(float3(.17, .04, .17));
		queenBib2->translate(float3(0, .6, 0) + queenOffset);

		Quadric* queenStem(new Quadric(queenMat));
		queenStem->hyperboloid();
		queenStem->scale(float3(0.1, .5, .1));
		queenStem->translate(float3(0, .5, 0) + queenOffset);
		
		Quadric* queenStemClipper(new Quadric(queenMat));
		queenStemClipper->parallelPlanes();
		queenStemClipper->scale(float3(1, .5, 1));
		queenStemClipper->translate(float3(0, .2, 0) + queenOffset);

		Quadric* queenHead(new Quadric(queenMat));
		queenHead->scale(float3(0.175, 0.175, 0.175));
		queenHead->translate(float3(0, .85, 0) + queenOffset);

		Quadric* queenCrown(new Quadric(queenMat));
		queenCrown->paraboloid();
		queenCrown->scale(float3(1.2, 4, 1.2));
		queenCrown->translate(float3(0, .85, 0) + queenOffset);

		Quadric* queenCrownClipper(new Quadric(queenMat));
		queenCrownClipper->parallelPlanes();
		queenCrownClipper->scale(float3(1, .15, 1));
		queenCrownClipper->translate(float3(0, .85, 0) + queenOffset);

		Quadric* queenTip(new Quadric(queenMat));
		queenTip->scale(float3(.03, .03, .03));
		queenTip->translate(float3(0, 1.04, 0) + queenOffset);

		objects.push_back(queenBase);
		objects.push_back(queenBib1);
		objects.push_back(queenBib2);
		objects.push_back(queenHead);
		objects.push_back(queenTip);
		objects.push_back(new ClippedQuadric(
			queenStem,
			queenStemClipper,
			queenMat));

		objects.push_back(new ClippedQuadric(
			queenCrown,
			queenCrownClipper,
			queenMat));
		
		//////////////////////////////////////////////////////////
		//King
		
		float3 kingOffset = float3(1, -1.6, .5);
		Material* kingMat = materials[6];

		Quadric* kingBase(new Quadric(kingMat));
		kingBase->scale(float3(.25, .1, .25));
		kingBase->translate(float3(0, -.35, 0) + kingOffset);

		Quadric* kingBib1(new Quadric(kingMat));
		kingBib1->scale(float3(.13, .03, .13));
		kingBib1->translate(float3(0, .7, 0) + kingOffset);

		Quadric* kingBib2(new Quadric(kingMat));
		kingBib2->scale(float3(.17, .04, .17));
		kingBib2->translate(float3(0, .6, 0) + kingOffset);

		Quadric* kingStem(new Quadric(kingMat));
		kingStem->hyperboloid();
		kingStem->scale(float3(0.1, .5, .1));
		kingStem->translate(float3(0, .5, 0) + kingOffset);

		Quadric* kingStemClipper(new Quadric(kingMat));
		kingStemClipper->parallelPlanes();
		kingStemClipper->scale(float3(1, .5, 1));
		kingStemClipper->translate(float3(0, .2, 0) + kingOffset);

		Quadric* kingHead(new Quadric(kingMat));
		kingHead->scale(float3(0.175, 0.175, 0.175));
		kingHead->translate(float3(0, .85, 0) + kingOffset);

		Quadric* kingCrown(new Quadric(kingMat));
		kingCrown->paraboloid();
		kingCrown->scale(float3(1.2, 4, 1.2));
		kingCrown->translate(float3(0, .85, 0) + kingOffset);

		Quadric* kingCrownClipper(new Quadric(kingMat));
		kingCrownClipper->parallelPlanes();
		kingCrownClipper->scale(float3(1, .15, 1));
		kingCrownClipper->translate(float3(0, .85, 0) + kingOffset);

		Quadric* kingCrossVert(new Quadric(kingMat));
		kingCrossVert->scale(float3(.03, .2, .03));
		kingCrossVert->translate(float3(0, 1.04, 0) + kingOffset);

		Quadric* kingCrossHorr(new Quadric(kingMat));
		kingCrossHorr->scale(float3(.1, .03, .03));
		kingCrossHorr->translate(float3(0, 1.14, 0) + kingOffset);

		objects.push_back(kingBase);
		objects.push_back(kingBib1);
		objects.push_back(kingBib2);
		objects.push_back(kingHead);
		objects.push_back(kingCrossVert);
		objects.push_back(kingCrossHorr);
		objects.push_back(new ClippedQuadric(
			kingStem,
			kingStemClipper,
			kingMat));

		objects.push_back(new ClippedQuadric(
			kingCrown,
			kingCrownClipper,
			kingMat));
		
		//////////////////////////////////////////////////////////
		
		objects.push_back(new Plane(float3(0, 1, 0), float3(0, -2, 0), materials[2]));

		
	}
	~Scene()
	{
		for (std::vector<Material*>::iterator iMaterial = materials.begin(); iMaterial != materials.end(); ++iMaterial)
			delete *iMaterial;
		for (std::vector<Intersectable*>::iterator iObject = objects.begin(); iObject != objects.end(); ++iObject)
			delete *iObject;		
	}

public:
	Camera& getCamera()
	{
		return camera;
	}

	Hit findIntersect(const Ray& ray) {
		
		Hit firstHit;
		Hit tempHit;
		float t = FLT_MAX;

		for (unsigned int i = 0; i < objects.size(); i++) {
			tempHit = objects[i]->intersect(ray);
			if (tempHit.t >= 0.0 && tempHit.t < t){
				firstHit = tempHit;
				t = firstHit.t;
			}
		}

		return firstHit;
	}

	float3 trace(const Ray& ray, int depth)
	{
		float3 color = float3(0.f, 0.f, 0.f);
		Hit hit = findIntersect(ray);
		float offset = 0.0001;

		if (hit.t < 0)
			return float3(1, 1, 1);



		for (std::size_t i = 0; i < lights.size(); i++) {
			Ray shadowRay(hit.position + hit.normal * offset,
				lights[i]->getLightDirAt(hit.position));
			Hit shadowHit = findIntersect(shadowRay);

			
			if (shadowHit.t < 0) {
				color += hit.material->shade(
					lights[i]->getPowerDensityAt(hit.position),
					lights[i]->getLightDirAt(hit.position),
					hit.normal,
					-ray.dir,
					hit.position
					);
			}			
		}

		if (depth > maxDepth)
			return float3(0, 0, 0);

		Metal* metal = dynamic_cast<Metal*>(hit.material);
		if (metal != NULL){
			Metal::Event e = metal->evaluateEvent(ray.dir, hit.normal);
			color += trace(Ray(hit.position + hit.normal, e.reflectionDir), depth++) * e.reflectance;
		}

		
		Dielectric* dielectric = dynamic_cast<Dielectric*>(hit.material);
		if (dielectric != NULL) {
			Dielectric::Event e = dielectric->evaluateEvent(ray.dir, hit.normal);
			color += trace(Ray(hit.position + hit.normal, e.reflectionDir), depth++) * e.reflectance;
			if (e.transmittance > 0)
				color += trace(Ray(hit.position - hit.position, e.refractionDir), depth++) * e.transmittance;
		}
		
		

		return color;
	}
};

