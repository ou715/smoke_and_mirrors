#include "triangle.h"

#include <iterator>

Triangle::Triangle() : a{ Vector3(-5, 0, -5) }, b{ Vector3(5, 0, -5) }, c{ Vector3(0, 5, -5) } {}
Triangle::Triangle(Vector3 a, Vector3 b, Vector3 c, Vector3 normal, ColourCoefficients diffuseCoefficients, ColourCoefficients specularCoefficients)
	: a{ a }, b{ b }, c{ c }, normal{normal}, diffuseReflectionCoefficients(diffuseCoefficients), specularReflectionCoefficients(specularCoefficients) {}

Triangle::Triangle(Vector3 a, Vector3 b, Vector3 c, Vector3 normal, ColourCoefficients diffuseCoefficients, ColourCoefficients specularCoefficients, ColourCoefficients transmittanceCoefficients, float refractionIndex)
	: a{ a }, b{ b }, c{ c }, normal{normal}, diffuseReflectionCoefficients(diffuseCoefficients), specularReflectionCoefficients(specularCoefficients) {}


ColourCoefficients Triangle::getDiffuseReflectance() {
	return diffuseReflectionCoefficients;
}

ColourCoefficients Triangle::getSpecularReflectance() {
	return specularReflectionCoefficients;
}

ColourCoefficients Triangle::getTransmittance() {
	return transmittanceCoefficients;
}

bool Triangle::isConductor() {
	return conductor;
}

float Triangle::getRefractionIndex() {
	return refractionIndex;
}

bool Triangle::isTranslucent() {
	return (getRefractionIndex() == 0) ? false : true;
}

Vector3 Triangle::surfaceNormal(Vector3 pointOnSurface) {
	return normal;
}

rayIntersection Triangle::rayHit(Ray ray) {
	constexpr float epsilon = 1.0e-10f;
	Vector3 rayDirection = ray.direction;

	Vector3 edgeAB = this->b - this->a;
	Vector3 edgeAC = this->c - this->a;
	Vector3 q = cross(rayDirection, edgeAC);

	float angle = dot(edgeAB, q);

	Vector3 rayOriginToA = ray.origin - this->a;
	Vector3 r = cross(rayOriginToA, edgeAB);

	float bary2 = dot(rayOriginToA, q) / angle;
	float bary3 = dot(rayDirection, r) / angle;
	float bary1 = 1.0f - (bary2 + bary3);

	float t = (dot(edgeAC, r) / angle);

	//First check is the side of the triangle we're looking at
	//Second, third, and fourth are checking is this point where the ray intersects the triangle's plane inside the triangle
	//Last check is if the triangle is behind the origin of the ray
	if ((angle <= epsilon) || (t <= 0) || (bary1 < -epsilon) || (bary2 < -epsilon) || (bary3 < -epsilon) ) {
		return rayIntersection{ false, INFINITY };

	} else {
		return rayIntersection{ true, t };
	}
}