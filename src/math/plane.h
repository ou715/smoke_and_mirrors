#pragma once

#include "geometry.h"
#include "../utility/utility.h"
#include "vector3.h"
#include "../physics/surface.h"

class Plane : public Surface {
public:
	Vector3 normal;
	Vector3 point;
	//Colourwise sum should be smaller than 0
	ColourCoefficients diffuseReflectionCoefficients;
	ColourCoefficients specularReflectionCoefficients; // Should only change the colour if it is a metallic surface
	ColourCoefficients transmittanceCoefficients;
	bool conductor = false;
	//Zero means opaque, for now
	float refractionIndex = 0;

	Plane();
	Plane(Vector3 normal, Vector3 point, ColourCoefficients diffuseCoefficients, ColourCoefficients specularCoefficients);
	Plane(Vector3 normal, Vector3 point, ColourCoefficients diffuseCoefficients, ColourCoefficients specularCoefficients, bool mirrorness);

	rayIntersection rayHit(Ray ray) override;
	Vector3 surfaceNormal(Vector3 pointOnSurface) override;
	ColourCoefficients getDiffuseReflectance() override;
	ColourCoefficients getSpecularReflectance() override;
	ColourCoefficients getTransmittance() override;
	bool isConductor() override;
	float getRefractionIndex() override;
	bool isTranslucent() override;
};