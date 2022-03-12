#include "raytrace.h"

Colour raytrace(Ray ray, int* maxRayDepth, Scene* scene, Colour totalLight, ColourCoefficients totalSpecularCoefficients, int numberOfRays) {
	//float lightIntensity = 3.0f;

	//TODO check light intensity
	if (numberOfRays > *maxRayDepth) {
		return totalLight;
	} else {
		intersectionInformation tracedPath = trace(ray, 0.00001f, INFINITY, scene);
		if (!tracedPath.firstIntersection.intersected) {
			return totalLight;
		} else {
			ColourCoefficients specularCoefficient = totalSpecularCoefficients * tracedPath.surfaceHit->getSpecularReflectance();
			Colour diffuseLight = shade(tracedPath, ray, scene);
			Colour addLight = diffuseLight * totalSpecularCoefficients;
			Vector3 normal = tracedPath.normal;
			Vector3 nextRayDirection = ray.direction - 2 * dot(ray.direction, normal) * normal;
			Ray nextRay = Ray(tracedPath.firstIntersectionPoint, nextRayDirection);
			if (tracedPath.surfaceHit->isTranslucent()) {
				float n2 = tracedPath.surfaceHit->getRefractionIndex();
				float relativeRefractionIndex = 1 / n2;
				Vector3 incidentRayDirection = normalise(ray.direction);
				if (dot(incidentRayDirection, normal) > 0) {
					normal = - normal;
					relativeRefractionIndex = 1 / relativeRefractionIndex;
				}
				float discriminant = sqrt(1 - (relativeRefractionIndex) * (relativeRefractionIndex) * (1 - pow(dot(normal, incidentRayDirection), 2)));
				if (discriminant > 0) {
					Vector3 directionOfRefractedRay = relativeRefractionIndex * (incidentRayDirection - normal * dot(incidentRayDirection, normal)) - normal * discriminant;
					Ray refractionRay = Ray(tracedPath.firstIntersectionPoint, directionOfRefractedRay);
					ColourCoefficients transmittance = totalSpecularCoefficients * tracedPath.surfaceHit->getTransmittance();
					Colour transmittedLight = totalLight * transmittance;
					addLight = addLight + raytrace(refractionRay, maxRayDepth, scene, transmittedLight, transmittance, numberOfRays + 1); //TODO convert to tail recursion
				} //else addLight = addLight + diffuseLight * tracedPath.surfaceHit->getTransmittance(); //TODO Total refraction
			}
			return raytrace(nextRay, maxRayDepth, scene, totalLight + addLight, specularCoefficient, numberOfRays + 1);
		}
	}
}