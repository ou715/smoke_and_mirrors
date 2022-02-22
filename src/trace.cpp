#include "trace.h"

#include <iostream>
#include <string>
#include <vector>

Path trace(Object **objects, Ray ray, size_t numberOfObjects){
	//std::cout << std::to_string(numberOfObjects) << "\n";
	rayIntersection firstIntersection{ false };
	float distanceToIntersection = INFINITY;
	Path tracedPath { firstIntersection , Vector3(), nullptr };
	for (size_t i = 0; i < numberOfObjects; i++) {
		//std::cout << "Index: " << std::to_string(i) << "\n";
		//if (&objects[i] != nullptr) {
			const rayIntersection rayIntersection = objects[i]->rayHit(ray);
			if (rayIntersection.intersected && rayIntersection.t > 0 && rayIntersection.t < distanceToIntersection) {
				firstIntersection = rayIntersection;
				distanceToIntersection = firstIntersection.t;
				Object *objectHit = objects[i];
				Vector3 intersectionPoint = ray.pointOnRay(firstIntersection.t);
				tracedPath = { firstIntersection, intersectionPoint, objectHit };
			}
		//} else continue;
	} 

return tracedPath;
}
