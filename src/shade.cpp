#include "shade.h"

Colour shade(Path path, Ray ray, PointLight** lights, size_t numberOfLights, Surface** objects, size_t numberOfObjects ) {
	ColourCoefficients surfaceDiffuseReflectance = path.surfaceHit->getCoefficients();
	Colour illuminatedColour = Colour(0, 0, 0);
	for (size_t i = 0; i < numberOfLights; i++) {
		Vector3 rayOfLightDirection = lights[i]->rayFromPointToLight(path.firstIntersectionPoint);
		Vector3 normalisedRayOfLightDirection = normalise(rayOfLightDirection);
		Ray fromIntersectionToLight = Ray(path.firstIntersectionPoint , rayOfLightDirection);
		float intersectionToLightDistance = rayOfLightDirection.length();
		Path shadowPath = trace(objects, fromIntersectionToLight, numberOfObjects, 0.1f, 1.0f);
		if (!shadowPath.firstIntersection.intersected) {
			float cameraLightDistance = rayOfLightDirection.length() + path.firstIntersectionPoint.length();
			Vector3 normal = path.surfaceHit->surfaceNormal(path.firstIntersectionPoint);
			float lambertianReflectanceCoefficient = std::max(0.0f, dot(path.surfaceHit->surfaceNormal(path.firstIntersectionPoint), normalisedRayOfLightDirection));
			illuminatedColour = illuminatedColour + ((lights[i]->colour * surfaceDiffuseReflectance) * lambertianReflectanceCoefficient);
		}
	}
	return illuminatedColour;
}
