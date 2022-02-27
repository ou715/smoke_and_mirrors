#include "sphere.h"

Sphere::Sphere() : radius(1), centre(Vector3()), diffuseReflectionCoefficients({0.5, 0.5, 0.5}) {};
Sphere::Sphere(float radius, Vector3 centre, ColourCoefficients diffuseCoefficients, ColourCoefficients specularColourCoefficients)
	: radius(radius), centre(centre), diffuseReflectionCoefficients(diffuseCoefficients), specularReflectionCoefficients{ specularColourCoefficients } {};

ColourCoefficients Sphere::getDiffuseReflectance() {
	return diffuseReflectionCoefficients;
}

ColourCoefficients Sphere::getSpecularReflectance() {
	return specularReflectionCoefficients;
}

rayIntersection Sphere::rayHit(Ray ray) {
	float lineDirectionNorm = ray.direction.length_squared();
	float discriminant = std::pow(dot(ray.direction, ray.origin - centre), 2)
		- (lineDirectionNorm * ((ray.origin - centre).length_squared() - radius * radius));
	if (discriminant > 0) {
		//TODO fix intersection code for spheres
		const float t = (-(dot(ray.direction, (ray.origin - centre))) - std::sqrt(discriminant)) * (1.0f / lineDirectionNorm);
		return rayIntersection{ true, t };
	} else	return rayIntersection{ false,  -INFINITY };
}

Vector3 Sphere::surfaceNormal(Vector3 pointOnSurface) {
	Vector3 normal = normalise((pointOnSurface - centre));
	return normal;
}