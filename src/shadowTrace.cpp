#include "shadowTrace.h"

bool shadowTrace(Surface** objects, Ray ray, size_t numberOfObjects, float tMin, float tMax) {
	for (size_t i = 0; i < numberOfObjects; i++) {
		const rayIntersection rayIntersection = objects[i]->rayHit(ray);
		if (rayIntersection.intersected && rayIntersection.t > tMin && rayIntersection.t < tMax) {
			return true;
		}
	}
	return false;
}