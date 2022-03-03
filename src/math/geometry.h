#pragma once

#include <cmath>

#include "../utility/utility.h"
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



