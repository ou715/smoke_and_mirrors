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
	virtual ColourCoefficients getCoefficients() = 0;
};

class Plane : public Surface {
public:
	Vector3 normal;
	Vector3 point;
	ColourCoefficients diffuseReflectionCoefficients; // Could be a different type

	Plane();
	Plane(Vector3 normal, Vector3 point, ColourCoefficients diffusionCoefficients);

	rayIntersection rayHit(Ray ray) override;
	Vector3 surfaceNormal(Vector3 pointOnSurface) override;
	ColourCoefficients getCoefficients() override;
};


struct Path {
	rayIntersection firstIntersection;
	Vector3 firstIntersectionPoint;
	Surface* surfaceHit;
};