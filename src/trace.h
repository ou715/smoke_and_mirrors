#pragma once
#include "math/geometry.h"

struct intersectionInformation {
	rayIntersection firstIntersection;
	Vector3 firstIntersectionPoint = Vector3();
	Vector3 normal = Vector3();
	Surface* surfaceHit = nullptr;
};

intersectionInformation trace(Surface** objects, Ray ray, size_t numberOfObjects, float tMin, float tMax);