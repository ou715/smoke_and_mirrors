#include "shade.h"

Colour shade(Path path, Ray ray, PointLight** lights, size_t numberOfLights, Surface** objects, size_t numberOfObjects ) {
	ColourCoefficients surfaceDiffuseReflectance = path.surfaceHit->getDiffuseReflectance();
	ColourCoefficients surfaceSpecularReflectance = path.surfaceHit->getSpecularReflectance();
	Colour illuminatedColour = Colour(0, 0, 0);
	for (size_t i = 0; i < numberOfLights; i++) {
		Vector3 rayOfLightDirection = lights[i]->rayFromPointToLight(path.firstIntersectionPoint);
		Vector3 normalisedRayOfLightDirection = normalise(rayOfLightDirection);
		Ray fromIntersectionToLight = Ray(path.firstIntersectionPoint , rayOfLightDirection);
		float intersectionToLightDistance = rayOfLightDirection.length();
		bool shadowPath = shadowTrace(objects, fromIntersectionToLight, numberOfObjects, 0.01f, 1.0f);
		if (shadowPath) {
			float cameraLightDistance = rayOfLightDirection.length() + path.firstIntersectionPoint.length();
			Vector3 normal = path.surfaceHit->surfaceNormal(path.firstIntersectionPoint);
			Vector3 halfPointVector = rayOfLightDirection + (-ray.direction);
			Vector3 normalisedHalfPointVector = halfPointVector / (halfPointVector.length());
			float lambertianReflectanceCoefficient = std::max(0.0f, dot(normal, normalisedRayOfLightDirection));
			float blinnPhongShading = std::pow(std::max(0.0f, dot(normal, normalisedHalfPointVector)),50);
			illuminatedColour = illuminatedColour + ((lights[i]->colour * surfaceDiffuseReflectance * lights[i]->intensity) * lambertianReflectanceCoefficient
														+ (lights[i]->colour * surfaceSpecularReflectance * lights[i]->intensity) * blinnPhongShading);
		}
	}
	return illuminatedColour;
}
