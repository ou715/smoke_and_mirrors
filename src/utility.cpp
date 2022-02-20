#include "utility.h"

#include <iostream>
#include <math.h>
#include <random>
#include <limits>
#include <string>

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
	return (vector_a.x * vector_b.x + vector_a.y * vector_b.y + vector_a.z * vector_b.z);
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

Ray::Ray() : passesThrough{ Vector3() } , parallelTo{ Vector3(1,1,1) } {}

Ray::Ray(Vector3 point, Vector3 vector) : passesThrough{ point }, parallelTo{ vector }  {}

Vector3 Ray::pointOnRay(float t) {
	return this->passesThrough + t * this->parallelTo;
}

/*
 * The default colour is gray.
 */
Colour::Colour() : red{ 100 }, green{ 100 }, blue{ 100 } {}

Colour::Colour(int r, int g, int b) : red{ r }, green{ g }, blue{ b } {}

Colour Colour::operator+(Colour colour) {
	return Colour(this->red += colour.red
		, this->green += colour.green
		, this->blue += colour.blue);
}

Colour Colour::operator-(Colour otherColour) {
	return Colour(this->red -= otherColour.red
		, this->green -= otherColour.green
		, this->blue -= otherColour.blue);
}

Plane::Plane() : normal{ Vector3(0, 0, 1) }, point{ Vector3(0, 1, 1) }, colour(Colour()) {}
Plane::Plane(Vector3 normal, Vector3 point, Colour colour) : normal{ normal }, point{ point }, colour(colour) {}

rayIntersection Plane::rayHit(Ray ray) {
	constexpr float epsilon = 1.0e-20;
	const float rayDirectionDotPlaneNormal = dot(normal, ray.parallelTo);
	if (abs(rayDirectionDotPlaneNormal) <= epsilon) {
		return rayIntersection{ false, Vector3(INFINITY, INFINITY, INFINITY), -INFINITY, Colour() };
	}
	else {
		const float originsDifferenceDotNormal = dot(normal, point - ray.passesThrough);
		if (abs(originsDifferenceDotNormal) <= epsilon) {
			return rayIntersection{ false, Vector3(INFINITY, INFINITY, INFINITY), -INFINITY, Colour() }; //Should be reworked in the future
		}
		else {
			const float t = originsDifferenceDotNormal / rayDirectionDotPlaneNormal;
			const Vector3 pointOfIntersection = ray.pointOnRay(t);
			return rayIntersection{ true, pointOfIntersection, t, colour };
		}
	}
}

Sphere::Sphere() : radius(1), centre(Vector3()), colour(Colour()){};
Sphere::Sphere(float radius, Vector3 centre, Colour colour) : radius(radius), centre(centre), colour(colour) {};

rayIntersection Sphere::rayHit(Ray ray) {
	float discriminant = std::pow(dot(ray.parallelTo, ray.passesThrough - centre), 2)
							- ((ray.passesThrough - centre).length_squared() - radius*radius);
	if (discriminant > 0) {
		//std::cout << "Sphere hit \n";
		const float t = -(dot(ray.parallelTo, (ray.passesThrough - centre))) - std::sqrt(discriminant);
		const Vector3 pointOfIntersection = ray.pointOnRay(t);
		return rayIntersection{ true, pointOfIntersection, t, colour };
	} else	return rayIntersection{ false, Vector3(INFINITY, INFINITY, INFINITY), -INFINITY, Colour() };
}

Camera::Camera() : cameraLocation{ Vector3() }, up{ Vector3(0, 1, 0) }, viewingDirection{ Vector3(0, 0, -1) }, horizontal{ 2 }, vertical{ 2 }{}
Camera::Camera(Vector3 location, Vector3 up, Vector3 viewingDirection, float horizontal, float vertical) :
			cameraLocation{location}
			, up{up}
			, viewingDirection{viewingDirection}
			, horizontal{horizontal}
			, vertical{ 2 } {}

bool compareRayIntersectionsByZ(rayIntersection a, rayIntersection b) {
	return a.intersectionPoint.z > b.intersectionPoint.z;
}
