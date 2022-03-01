#pragma once

#include <cmath>

#include "../utility.h"
#include "vector3.h"

class Ray {
public:
	Vector3 origin;
	Vector3 direction;

	Ray();
	Ray(Vector3 origin, Vector3 direction);

	Vector3 pointOnRay(float t);
};

struct rayIntersection {
	bool intersected = false;
	float t = INFINITY;
};

class Surface {
public:
	virtual rayIntersection rayHit(Ray ray) = 0;
	virtual Vector3 surfaceNormal(Vector3 pointOnSurface) = 0;
	virtual ColourCoefficients getDiffuseReflectance() = 0;
	virtual ColourCoefficients getSpecularReflectance() = 0;
	virtual bool isConductor() = 0;
};

class Plane : public Surface {
public:
	Vector3 normal;
	Vector3 point;
	//Colourwise sum should be smaller than 0
	ColourCoefficients diffuseReflectionCoefficients;
	ColourCoefficients specularReflectionCoefficients; // Should only change the colour if it is a metallic surface
	bool conductor = false;

	Plane();
	Plane(Vector3 normal, Vector3 point, ColourCoefficients diffuseCoefficients, ColourCoefficients specularCoefficients);
	Plane(Vector3 normal, Vector3 point, ColourCoefficients diffuseCoefficients, ColourCoefficients specularCoefficients, bool mirrorness);

	rayIntersection rayHit(Ray ray) override;
	Vector3 surfaceNormal(Vector3 pointOnSurface) override;
	ColourCoefficients getDiffuseReflectance() override;
	ColourCoefficients getSpecularReflectance() override;
	bool isConductor() override;
};


