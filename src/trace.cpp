#include "trace.h"

intersectionInformation trace(Surface **objects, Ray ray, size_t numberOfObjects, float tMin, float tMax){
	//std::cout << std::to_string(numberOfObjects) << "\n";
	rayIntersection firstIntersection{ false };
	float distanceToIntersection = INFINITY;
	float y = ray.origin.y;
	float z = ray.origin.z;
	intersectionInformation tracedPath { firstIntersection };
	for (size_t i = 0; i < numberOfObjects; i++) {
		const rayIntersection rayIntersection = objects[i]->rayHit(ray);
		if (rayIntersection.intersected && rayIntersection.t > tMin && rayIntersection.t < tMax && rayIntersection.t < distanceToIntersection) {
			firstIntersection = rayIntersection;
			distanceToIntersection = firstIntersection.t;
			Surface *objectHit = objects[i];
			Vector3 intersectionPoint = ray.pointOnRay(firstIntersection.t);
			Vector3 normal = objectHit->surfaceNormal(intersectionPoint);
			tracedPath = { firstIntersection, intersectionPoint, normal, objectHit };
		}
	} 
return tracedPath;
}