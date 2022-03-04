#include "trace.h"

intersectionInformation trace(Ray ray,float tMin, float tMax, Scene* scene){
	//std::cout << std::to_string(numberOfObjects) << "\n";
	rayIntersection firstIntersection{ false };
	float distanceToIntersection = INFINITY;
	float y = ray.origin.y;
	float z = ray.origin.z;
	intersectionInformation tracedPath { firstIntersection };
	for (size_t i = 0; i < scene->numberOfObjects; i++) {
		const rayIntersection rayIntersection = scene->objects[i]->rayHit(ray);
		if (rayIntersection.intersected && rayIntersection.t > tMin && rayIntersection.t < tMax && rayIntersection.t < distanceToIntersection) {
			firstIntersection = rayIntersection;
			distanceToIntersection = firstIntersection.t;
			Surface *objectHit = scene->objects[i];
			Vector3 intersectionPoint = ray.pointOnRay(firstIntersection.t);
			Vector3 normal = objectHit->surfaceNormal(intersectionPoint);
			tracedPath = { firstIntersection, intersectionPoint, normal, objectHit };
		}
	} 
return tracedPath;
}