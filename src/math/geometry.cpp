#include <cmath>

#include "geometry.h"



Ray::Ray() : origin{ Vector3() }, direction{ Vector3(1,1,1) } {}

Ray::Ray(Vector3 origin, Vector3 direction) : origin{ origin }, direction{ direction }  {}

Vector3 Ray::pointOnRay(float t) {
	return this->origin + t * this->direction;
}
