#include "plane.h"


Plane::Plane() : normal{ Vector3(0, 0, 1) }, point{ Vector3(0, 1, 1) }, diffuseReflectionCoefficients({ 0.5, 0.5, 0.5 }) {}
Plane::Plane(Vector3 normal, Vector3 point, ColourCoefficients diffuseCoefficients, ColourCoefficients specularCoefficients)
	: normal{ normalise(normal) }, point{ point }, diffuseReflectionCoefficients(diffuseCoefficients), specularReflectionCoefficients{ specularCoefficients } {}

Plane::Plane(Vector3 normal, Vector3 point, ColourCoefficients diffuseCoefficients, ColourCoefficients specularCoefficients, bool conductor)
	: normal{ normalise(normal) }, point{ point }, diffuseReflectionCoefficients(diffuseCoefficients), specularReflectionCoefficients{ specularCoefficients }, conductor{ conductor } {}


ColourCoefficients Plane::getDiffuseReflectance() {
	return diffuseReflectionCoefficients;
}

ColourCoefficients Plane::getSpecularReflectance() {
	return specularReflectionCoefficients;
}

bool Plane::isConductor() {
	return conductor;
}

float Plane::getRefractionIndex() {
	return refractionIndex;
}

rayIntersection Plane::rayHit(Ray ray) {
	constexpr float epsilon = 1.0e-20f;
	const float rayDirectionDotPlaneNormal = dot(normal, ray.direction);
	if (abs(rayDirectionDotPlaneNormal) <= epsilon) {
		return rayIntersection{ false,  -INFINITY };
	} else {
		const float originsDifferenceDotNormal = dot(normal, point - ray.origin);
		if (abs(originsDifferenceDotNormal) <= epsilon) {
			return rayIntersection{ false,  -INFINITY }; //Should be reworked in the future
		} else {
			const float t = originsDifferenceDotNormal / rayDirectionDotPlaneNormal;
			return rayIntersection{ true,  t };
		}
	}
}

Vector3 Plane::surfaceNormal(Vector3 pointOnSurface) {
	return normal;
}