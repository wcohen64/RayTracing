#define _USE_MATH_DEFINES
#include "stdafx.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>
 
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define NOMINMAX
#include <windows.h>
#endif 
 
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "float2.h"
#include "float3.h"
#include "float4.h"
#include "float4x4.h"
#include "Scene.h"
#include "QuadraticRoots.h"
#include "Ray.h"
#include <vector>


using namespace std;


class Sphere : public Intersectable
{
	float3 center;
	float radius;
public:
    Sphere(const float3& center, float radius, Material* material):
		Intersectable(material),
		center(center),
		radius(radius)
    {
    }
	QuadraticRoots solveQuadratic(const Ray& ray)
	{
        float3 diff = ray.origin - center;
        float a = ray.dir.dot(ray.dir);
        float b = diff.dot(ray.dir) * 2.0;
        float c = diff.dot(diff) - radius * radius;
		return QuadraticRoots(a, b, c);
 
	}
	float3 getNormalAt(float3 r)
	{
		return (r - center).normalize();
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
}; 

////////////////////////////////////////////////////////////////////////////////////////////////////////
// global application data

const int screenWidth = 600;
const int screenHeight = 600;
float3 image[screenWidth*screenHeight];

Scene scene;

bool computeImage()
{
	static unsigned int iPart = 0;

	if(iPart >= 64)
		return false;
    for(int j = iPart; j < screenHeight; j+=64)
	{
        for(int i = 0; i < screenWidth; i++)
		{
			float3 pixelColor = float3(0, 0, 0);
			float2 ndcPixelCentre( (2.0 * i - screenWidth) / screenWidth, (2.0 * j - screenHeight) / screenHeight );

			Camera& camera = scene.getCamera();
			Ray ray = Ray(camera.getEye(), camera.rayDirFromNdc(ndcPixelCentre));
			
			image[j*screenWidth + i] = scene.trace(ray,0);
		}
	}
	iPart++;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void onDisplay( ) {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	if(computeImage())
		glutPostRedisplay();
    glDrawPixels(screenWidth, screenHeight, GL_RGB, GL_FLOAT, image);
 
    glutSwapBuffers(); 
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);						
    glutInitWindowSize(screenWidth, screenHeight);		
    glutInitWindowPosition(100, 100);         
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);    
 
    glutCreateWindow("Ray caster");				
 
    glViewport(0, 0, screenWidth, screenHeight);

    glutDisplayFunc(onDisplay);					
 
    glutMainLoop();								
    
    return 0;
}

