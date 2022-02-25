#include "shade.h"



Colour shade(Path path, Ray ray, PointLight** lights, size_t numberOfLights, Object** objects, size_t numberOfObjects ) {
	Colour baseColourOfIntersection = path.objectHit->getColour();
	Colour illuminatedColour = Colour(0, 0, 0);
	for (size_t i = 0; i < numberOfLights; i++) {
		Vector3 rayOfLightDirection = lights[i]->rayFromPointToLight(path.firstIntersectionPoint);
		Vector3 normalisedRayOfLightDirection = normalise(rayOfLightDirection);
		Ray fromIntersectionToLight = Ray(path.firstIntersectionPoint , rayOfLightDirection);
		float intersectionToLightDistance = rayOfLightDirection.length();
		//Path shadowPath = trace(objects, fromIntersectionToLight, numberOfObjects, -0.8f, -0.2f);
		//std::cout << "x: " << std::to_string(fromIntersectionToLight.origin.x) << " y: " << std::to_string(fromIntersectionToLight.origin.y) << " z: " << std::to_string(fromIntersectionToLight.origin.z) << "\n";
		//if (!shadowPath.firstIntersection.intersected) {

			float cameraLightDistance = rayOfLightDirection.length() + path.firstIntersectionPoint.length();
			Vector3 normal = path.objectHit->surfaceNormal(path.firstIntersectionPoint);
			float lambertianReflectanceCoefficient = std::max(0.0f, dot(path.objectHit->surfaceNormal(path.firstIntersectionPoint), normalisedRayOfLightDirection));
			illuminatedColour = illuminatedColour + (baseColourOfIntersection * lights[i]->intensity * lambertianReflectanceCoefficient);
		//} else {
		//	std::cout << "Light blocked! \n";
		//	std::cout << "x: " << std::to_string(path.firstIntersectionPoint.x) << " y: " << std::to_string(path.firstIntersectionPoint.y) << " z: " << std::to_string(path.firstIntersectionPoint.z) << "\n";
		//	std::cout << std::to_string(shadowPath.objectHit->getColour().blue) << " \n";
		//}
	}
	return illuminatedColour;
}
