#pragma once
#include "geometry.h"
#include "../utility/utility.h"
#include "../physics/surface.h"

class Sphere : public Surface {
public:
	float radius;
	Vector3 centre;
	ColourCoefficients diffuseReflectionCoefficients;
	ColourCoefficients specularReflectionCoefficients;
	ColourCoefficients transmittanceCoefficients;
	bool conductor = false;
	float refractionIndex = 0;

	Sphere();
	Sphere(float radius, Vector3 centre, ColourCoefficients diffuseCoefficients, ColourCoefficients specularCoefficients);
	Sphere(float radius, Vector3 centre, ColourCoefficients diffuseCoefficients, ColourCoefficients specularCoefficients, bool isConductor);
	Sphere(float radius, Vector3 centre, ColourCoefficients diffuseCoefficients, ColourCoefficients specularCoefficients, ColourCoefficients transmittanceCoefficients, float refractionIndex);
	rayIntersection rayHit(Ray ray) override;
	Vector3 surfaceNormal(Vector3 pointOnSurface) override;
	ColourCoefficients getDiffuseReflectance() override;
	ColourCoefficients getSpecularReflectance() override;
	ColourCoefficients getTransmittance() override;
	bool isConductor() override;
	float getRefractionIndex() override;
	bool isTranslucent() override;
};