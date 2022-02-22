#include "shade.h"


Colour shade(Path path, Ray ray, PointLight** lights, size_t numberOfLights) {
	Colour baseColourOfIntersection = path.objectHit->getColour();
	Colour illuminatedColour = Colour(0, 0, 0);
	for (size_t i = 0; i < numberOfLights; i++) {
		Vector3 rayOfLightDirection = lights[i]->rayFromLightToPoint(path.firstIntersectionPoint);
		Vector3 normalisedRayOfLightDirection = normalise(rayOfLightDirection);
		float cameraLightDistance = rayOfLightDirection.length() + path.firstIntersectionPoint.length();
		float lambertianReflectanceCoefficient = std::max(0.0f, dot(path.objectHit->surfaceNormal(path.firstIntersectionPoint), normalisedRayOfLightDirection));
		illuminatedColour = illuminatedColour + (baseColourOfIntersection * lights[i]->intensity * lambertianReflectanceCoefficient);
	}

	return illuminatedColour;
}
