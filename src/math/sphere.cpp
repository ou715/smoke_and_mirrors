#include "sphere.h"

Sphere::Sphere() : radius(1), centre(Vector3()), diffuseReflectionCoefficients({0.5, 0.5, 0.5}) {};
Sphere::Sphere(float radius, Vector3 centre, ColourCoefficients diffuseCoefficients, ColourCoefficients specularCoefficients)
	: radius(radius), centre(centre), diffuseReflectionCoefficients(diffuseCoefficients), specularReflectionCoefficients{ specularCoefficients } {};

Sphere::Sphere(float radius, Vector3 centre, ColourCoefficients diffuseCoefficients, ColourCoefficients specularCoefficients, bool conductor)
	: radius(radius), centre(centre), diffuseReflectionCoefficients(diffuseCoefficients), specularReflectionCoefficients{ specularCoefficients }, conductor(conductor) {};

Sphere::Sphere(float radius, Vector3 centre, ColourCoefficients diffuseCoefficients, ColourCoefficients specularCoefficients, ColourCoefficients transmittanceCoefficients, float refractionIndex)
	: radius(radius), centre(centre), diffuseReflectionCoefficients(diffuseCoefficients), specularReflectionCoefficients{ specularCoefficients }, transmittanceCoefficients{ transmittanceCoefficients }, refractionIndex{ refractionIndex } {};

ColourCoefficients Sphere::getDiffuseReflectance() {
	return diffuseReflectionCoefficients;
}

ColourCoefficients Sphere::getSpecularReflectance() {
	return specularReflectionCoefficients;
}

ColourCoefficients Sphere::getTransmittance() {
	return transmittanceCoefficients;
}

bool Sphere::isConductor() {
	return conductor;
}

float Sphere::getRefractionIndex() {
	return refractionIndex;
}

bool Sphere::isTranslucent() {
	return (this->getRefractionIndex() == 0) ? false : true;
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
	Vector3 normal = (pointOnSurface - centre)/radius;
	return normal;
}