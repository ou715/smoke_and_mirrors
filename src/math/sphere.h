#pragma once
#include "geometry.h"
#include "../utility.h"

class Sphere : public Surface {
public:
	float radius;
	Vector3 centre;
	Colour colour;

	Sphere();
	Sphere(float radius, Vector3 centre, Colour colour);

	rayIntersection rayHit(Ray ray) override;
	Vector3 surfaceNormal(Vector3 pointOnSurface) override;
	Colour getColour() override;
};