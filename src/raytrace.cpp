#include "raytrace.h"


Colour raytrace(Ray ray, Scene* scene) {

	Colour illuminatedColour = Colour();
	float lightIntensity = 3.0f;
	ColourCoefficients totalSpecularCoefficients;
	int numberOfAdditionalRays = 3;

	intersectionInformation tracedPath = trace(ray, 1, INFINITY, scene);

	if (tracedPath.firstIntersection.intersected) {
		illuminatedColour = shade(tracedPath, ray, scene);
		Vector3 normal = tracedPath.normal;
		Vector3 secondRayDirection = ray.direction - (2 * dot(ray.direction, normal) * normal);
		Ray secondRay = Ray(tracedPath.firstIntersectionPoint, secondRayDirection);

		totalSpecularCoefficients = tracedPath.surfaceHit->getSpecularReflectance();

		//while (lightIntensity > .0001f) {
		//	intersectionInformation secondPath = trace(objects, secondRay, numberOfObjects, 0.010f, INFINITY);
		//	if (secondPath.firstIntersection.intersected) {
		//		Colour addLight = shade(secondPath, secondRay, lights, numberOfLights, objects, numberOfObjects) * totalSpecularCoefficients;
		//		illuminatedColour = illuminatedColour + addLight;
		//		lightIntensity = addLight.getIntensity();
		//		totalSpecularCoefficients = totalSpecularCoefficients * secondPath.surfaceHit->getSpecularReflectance();
		//		normal = secondPath.normal;
		//		secondRayDirection = secondRay.direction - 2 * dot(secondRay.direction, normal) * normal;
		//		secondRay = Ray(secondPath.firstIntersectionPoint, secondRayDirection);
		//	} else lightIntensity = 0.0f;
		//}
		//std::cout << "light too weak \n";

		//Reflection rays
		for (int i = 0; i < numberOfAdditionalRays; i++) {
			intersectionInformation secondPath = trace(secondRay, 0.010f, INFINITY, scene);
			if (secondPath.firstIntersection.intersected) {
				Colour addLight = shade(secondPath, secondRay, scene) * totalSpecularCoefficients;
				illuminatedColour = illuminatedColour + addLight;
				totalSpecularCoefficients = totalSpecularCoefficients * secondPath.surfaceHit->getSpecularReflectance();
				normal = secondPath.normal;
				secondRayDirection = secondRay.direction - 2 * dot(secondRay.direction, normal) * normal;
				secondRay = Ray(secondPath.firstIntersectionPoint, secondRayDirection);
			} else break;
		}


	}
	return illuminatedColour;
}
