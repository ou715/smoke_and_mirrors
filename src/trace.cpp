#include "trace.h"

#include <vector>

Path trace(Object *objects, Ray ray, int numberOfObjects){

	rayIntersection firstIntersection{ false };
	float distanceToIntersection = INFINITY;
	Path tracedPath;
	for (int i = 0; i < numberOfObjects; i++) {
		auto obj = &objects[i];
		rayIntersection rayIntersection = *(&objects[i].rayHit(ray));
		if (rayIntersection.intersected && rayIntersection.t > 0 && rayIntersection.t < distanceToIntersection) {
			firstIntersection = rayIntersection;
			distanceToIntersection = firstIntersection.t;
			Object *objectHit = &objects[i];
			Vector3 intersectionPoint = ray.pointOnRay(firstIntersection.t);
			float distance = intersectionPoint.length();
			tracedPath = { firstIntersection, intersectionPoint, objectHit,  distance };
		} else tracedPath = { firstIntersection , Vector3(), nullptr, INFINITY };
	}

return tracedPath;
}
