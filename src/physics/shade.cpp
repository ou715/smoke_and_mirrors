#include "shade.h"

Colour shade(intersectionInformation path, Ray ray, Scene* scene) {
	ColourCoefficients surfaceDiffuseReflectance = path.surfaceHit->getDiffuseReflectance();
	ColourCoefficients surfaceSpecularReflectance = path.surfaceHit->getSpecularReflectance();
	Colour illuminatedColour = Colour(0, 0, 0);
	Colour specularComponent;

	for (size_t i = 0; i < scene->numberOfLights; i++) {
		Vector3 rayOfLightDirection = scene->PointLights[i]->rayFromPointToLight(path.firstIntersectionPoint);
		Vector3 normalisedRayOfLightDirection = normalise(rayOfLightDirection);
		Ray fromIntersectionToLight = Ray(path.firstIntersectionPoint , rayOfLightDirection);
		//float intersectionToLightDistance = rayOfLightDirection.length();
		bool occluded = shadowTrace(fromIntersectionToLight, 0.01f, 1.0f, scene);
		if (!occluded) {
			//float cameraLightDistance = rayOfLightDirection.length() + path.firstIntersectionPoint.length();
			Vector3 normal = path.surfaceHit->surfaceNormal(path.firstIntersectionPoint);
			//Vector3 halfPointVector = rayOfLightDirection + (-ray.direction);
			//Vector3 normalisedHalfPointVector = halfPointVector / (halfPointVector.length());
			float lambertianReflectanceCoefficient = std::max(0.0f, dot(normal, normalisedRayOfLightDirection));
			//float blinnPhongShading = std::pow(std::max(0.0f, dot(normal, normalisedHalfPointVector)),100);
			//specularComponent = (lights[i]->colour * surfaceSpecularReflectance * lights[i]->intensity) * blinnPhongShading;

			illuminatedColour = illuminatedColour + ((scene->PointLights[i]->colour * surfaceDiffuseReflectance * scene->PointLights[i]->intensity) * lambertianReflectanceCoefficient);
		}
	}
	return illuminatedColour;
}
