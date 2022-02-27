#pragma once
#include "geometry.h"
#include "../utility.h"

class Sphere : public Surface {
public:
	float radius;
	Vector3 centre;
	ColourCoefficients diffuseReflectionCoefficients; // Could be a different type

	Sphere();
	Sphere(float radius, Vector3 centre, ColourCoefficients diffuseCoefficients);

	rayIntersection rayHit(Ray ray) override;
	Vector3 surfaceNormal(Vector3 pointOnSurface) override;
	ColourCoefficients getCoefficients() override;
};