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


