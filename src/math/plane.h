#pragma once

#include "geometry.h"
#include "../utility/utility.h"
#include "vector3.h"

class Plane : public Surface {
public:
	Vector3 normal;
	Vector3 point;
	//Colourwise sum should be smaller than 0
	ColourCoefficients diffuseReflectionCoefficients;
	ColourCoefficients specularReflectionCoefficients; // Should only change the colour if it is a metallic surface
	bool conductor = false;

	Plane();
	Plane(Vector3 normal, Vector3 point, ColourCoefficients diffuseCoefficients, ColourCoefficients specularCoefficients);
	Plane(Vector3 normal, Vector3 point, ColourCoefficients diffuseCoefficients, ColourCoefficients specularCoefficients, bool mirrorness);

	rayIntersection rayHit(Ray ray) override;
	Vector3 surfaceNormal(Vector3 pointOnSurface) override;
	ColourCoefficients getDiffuseReflectance() override;
	ColourCoefficients getSpecularReflectance() override;
	bool isConductor() override;
};