#include "raytrace.h"

Colour raytrace(Ray ray, int* maxRayDepth, Scene* scene, Colour totalLight, ColourCoefficients totalSpecularCoefficients, int numberOfRays) {
	//float lightIntensity = 3.0f;

	//TODO check light intensity
	if (numberOfRays > *maxRayDepth) {
		return totalLight;
	} else {
		intersectionInformation tracedPath = trace(ray, 0.010f, INFINITY, scene);
		if (!tracedPath.firstIntersection.intersected) {
			return totalLight;
		} else {
			ColourCoefficients specularCoefficient = totalSpecularCoefficients * tracedPath.surfaceHit->getSpecularReflectance();
			Colour addLight = shade(tracedPath, ray, scene) * totalSpecularCoefficients;
			Vector3 normal = tracedPath.normal;
			Vector3 nextRayDirection = ray.direction - 2 * dot(ray.direction, normal) * normal;
			Ray nextRay = Ray(tracedPath.firstIntersectionPoint, nextRayDirection);
			return raytrace(nextRay, maxRayDepth, scene, totalLight + addLight, specularCoefficient, numberOfRays + 1);
		}
	}
}