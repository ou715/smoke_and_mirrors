#include "shadowTrace.h"

bool shadowTrace(Ray ray, float tMin, float tMax, Scene* scene) {
	for (size_t i = 0; i < scene->numberOfObjects; i++) {
		const rayIntersection rayIntersection = scene->objects[i]->rayHit(ray);
		if (rayIntersection.intersected && rayIntersection.t > tMin && rayIntersection.t < tMax && !scene->objects[i]->isTranslucent()) { //TODO Translucent objects actually attenuate light
			return true;
		}
	}
	return false;
}