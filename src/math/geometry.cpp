#include <cmath>

#include "geometry.h"

Ray::Ray() : origin{ Vector3() }, direction{ Vector3(1,1,1) } {}

Ray::Ray(Vector3 origin, Vector3 direction) : origin{ origin }, direction{ direction }  {}

Vector3 Ray::pointOnRay(float t) {
	return this->origin + t * this->direction;
}

Plane::Plane() : normal{ Vector3(0, 0, 1) }, point{ Vector3(0, 1, 1) }, colour(Colour()) {}
Plane::Plane(Vector3 normal, Vector3 point, Colour colour) : normal{ normal }, point{ point }, colour(colour) {}

Colour Plane::getColour() {
	return colour;
}

rayIntersection Plane::rayHit(Ray ray) {
	constexpr float epsilon = 1.0e-20;
	const float rayDirectionDotPlaneNormal = dot(normal, ray.direction);
	if (abs(rayDirectionDotPlaneNormal) <= epsilon) {
		return rayIntersection{ false,  -INFINITY };
	} else {
		const float originsDifferenceDotNormal = dot(normal, point - ray.origin);
		if (abs(originsDifferenceDotNormal) <= epsilon) {
			return rayIntersection{ false,  -INFINITY }; //Should be reworked in the future
		} else {
			const float t = originsDifferenceDotNormal / rayDirectionDotPlaneNormal;
			return rayIntersection{ true,  t };
		}
	}
}


Vector3 Plane::surfaceNormal(Vector3 pointOnSurface) {
	return normalise(normal);
}