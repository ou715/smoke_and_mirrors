#include "utility.h"
#include <math.h>


struct PPM ppm;

PPM transpose(PPM image, int n, int m){

	return image;
}


Vector3::Vector3(float xInit, float yInit, float zInit) {
	x = xInit;
	y = yInit;
	z = yInit;
}

Vector3::length() {
	return sqrt(x * x + y * y + z * z);
}