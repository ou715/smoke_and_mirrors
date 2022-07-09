#pragma once
#include "geometry.h"
#include "../physics/surface.h"
#include "../utility/utility.h"

class Triangle : public Surface {
public:
	Vector3 a, b, c;
	Vector3 normal;
	ColourCoefficients diffuseReflectionCoefficients;
	ColourCoefficients specularReflectionCoefficients;
	ColourCoefficients transmittanceCoefficients;
	bool conductor = false;
	float refractionIndex = 0;


	Triangle();
	Triangle(Vector3 a, Vector3 b, Vector3 c, Vector3 normal, ColourCoefficients diffuseCoefficients, ColourCoefficients specularCoefficients);
	Triangle(Vector3 a, Vector3 b, Vector3 c, Vector3 normal, ColourCoefficients diffuseCoefficients, ColourCoefficients specularCoefficients, ColourCoefficients transmittanceCoefficients, float refractionIndex);

	rayIntersection rayHit(Ray ray) override;
	Vector3 surfaceNormal(Vector3 pointOnSurface) override;
	ColourCoefficients getDiffuseReflectance() override;
	ColourCoefficients getSpecularReflectance() override;
	ColourCoefficients getTransmittance() override;
	bool isConductor() override;
	float getRefractionIndex() override;
	bool isTranslucent() override;
};