#pragma once
#include "geometry.h"
#include "../utility.h"

class Sphere : public Surface {
public:
	float radius;
	Vector3 centre;
	ColourCoefficients diffuseReflectionCoefficients;
	ColourCoefficients specularReflectionCoefficients;

	Sphere();
	Sphere(float radius, Vector3 centre, ColourCoefficients diffuseCoefficients, ColourCoefficients specularCoefficients);

	rayIntersection rayHit(Ray ray) override;
	Vector3 surfaceNormal(Vector3 pointOnSurface) override;
	ColourCoefficients getDiffuseReflectance() override;
	ColourCoefficients getSpecularReflectance() override;
};