#pragma once
#include "../math/geometry.h"

class Surface {
public:
	virtual rayIntersection rayHit(Ray ray) = 0;
	virtual Vector3 surfaceNormal(Vector3 pointOnSurface) = 0;
	virtual ColourCoefficients getDiffuseReflectance() = 0;
	virtual ColourCoefficients getSpecularReflectance() = 0;
	virtual ColourCoefficients getTransmittance() = 0;
	virtual bool isConductor() = 0;
	virtual bool isTranslucent() = 0;
	virtual float getRefractionIndex() = 0;
};
