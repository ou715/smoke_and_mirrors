#include "utility.h"
#include <math.h>
#include <random>


struct PPM ppm;

PPM transpose(PPM image, int n, int m){

	return image;
}

Vector3::Vector3() : x{ 0 }, y{ 0 }, z{ 0 } {}


Vector3::Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}


float Vector3::length() {
	return sqrt(x*x + y*y + z*z);
}

float Vector3::length_squared() {
	return x * x + y * y + z * z;
}

Vector3 Vector3::operator+(Vector3 otherVector) {
	return Vector3(this->x + otherVector.x
		, this->y + otherVector.y
		, this->z + otherVector.z);
}

Vector3 Vector3::operator-(Vector3 otherVector){
	return Vector3(this->x - otherVector.x
		, this->y - otherVector.y
		, this->z - otherVector.z);
}

Vector3 operator*(float c, Vector3 vector) {
	return Vector3(c * vector.x, c * vector.y, c * vector.z);
}

Vector3 operator*(Vector3 vector, float c) {
	return Vector3(c * vector.x, c * vector.y, c * vector.z);
}

float dot(Vector3 vector_a, Vector3 vector_b) {
	return (vector_a.x * vector_b.x + vector_a.y * vector_b.y + vector_a.z + vector_b.z);
}

Vector3 cross(Vector3 vector_a, Vector3 vector_b) {
	return Vector3(
		vector_a.y * vector_b.z - vector_a.z * vector_b.y
		, vector_a.z * vector_b.x - vector_a.x * vector_b.z
		, vector_a.x * vector_b.y - vector_a.y * vector_b.x
	);
}

Vector3 normalise(Vector3 vector) {
	float k = 1 / vector.length();
	return Vector3(k * vector.x, k * vector.y, k * vector.z);
}

Ray::Ray() : parallelTo{ Vector3(1,1,1) }, passesThrough{ Vector3() } {}

Ray::Ray(Vector3 vector, Vector3 point) : parallelTo{ vector }, passesThrough{ point } {}

Vector3 Ray::pointOnRay(float t) {
	return this->passesThrough + t * this->parallelTo;
}

/*
 * The default colour is lime. Could change in the future.
 */
Colour::Colour() {
	red = 50;
	green = 205;
	blue = 50;
}

Colour::Colour(int r, int g, int b) {
	red = r;
	green = g;
	blue = b;
}

Colour Colour::operator+(Colour otherColour) {
	return Colour(this->red += otherColour.red
		, this->green += otherColour.green
		, this->blue += otherColour.blue);
}

Colour Colour::operator-(Colour otherColour) {
	return Colour(this->red -= otherColour.red
		, this->green -= otherColour.green
		, this->blue -= otherColour.blue);
}

Plane::Plane() : normal{ Vector3(0, 0, 1) }, point{ Vector3(0, 1, 1) }, colour(Colour()) {}
Plane::Plane(Vector3 normal, Vector3 point, Colour colour) : normal{ normal }, point{ point }, colour(colour) {}

bool Plane::rayHit(Ray ray) {
	constexpr float epsilon = 0.000001f;
	const float rayDirectionDotPlaneNormal = dot(normal, ray.parallelTo);
	if (abs(rayDirectionDotPlaneNormal) >= epsilon) return false;
	else {
		const float originsDifferenceDotNormal = dot(normal, point - ray.parallelTo);
		if (abs(originsDifferenceDotNormal) <= epsilon) return false; //Should be reworked in the future
		else return true; //Return the number of hits in the future
	}
}


Camera::Camera() : cameraLocation{ Vector3() }, up{ Vector3(0, 1, 0) }, viewingDirection{ Vector3(0, 0, -1) }, horizontal{ 2 }, vertical{ 2 }{}
Camera::Camera(Vector3 location, Vector3 up, Vector3 viewingDirection, float horizontal, float vertical) :
			cameraLocation{location}
			, up{up}
			, viewingDirection{viewingDirection}
			, horizontal{horizontal}
			, vertical{ 2 } {}
