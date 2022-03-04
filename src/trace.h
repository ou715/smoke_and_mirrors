#pragma once
#include "math/geometry.h"
#include "physics/surface.h"
#include "utility/scene.h"

struct intersectionInformation {
	rayIntersection firstIntersection;
	Vector3 firstIntersectionPoint = Vector3();
	Vector3 normal = Vector3();
	Surface* surfaceHit = nullptr;
};

intersectionInformation trace(Ray ray, float tMin, float tMax, Scene* scene);