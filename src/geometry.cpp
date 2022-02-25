#include <cmath>

#include "geometry.h"



Vector3::Vector3() : x{ 0 }, y{ 0 }, z{ 0 } {}

Vector3::Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}

float Vector3::length() {
	return sqrt(x * x + y * y + z * z);
}

float Vector3::length_squared() {
	return x * x + y * y + z * z;
}

Vector3 Vector3::operator+(Vector3 otherVector) {
	return Vector3(this->x + otherVector.x
		, this->y + otherVector.y
		, this->z + otherVector.z);
}

Vector3 Vector3::operator-(Vector3 otherVector) {
	return Vector3(this->x - otherVector.x
		, this->y - otherVector.y
		, this->z - otherVector.z);
}

Vector3 Vector3::operator-() {
	return Vector3(-this->x, -this->y, -this->z);
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

Sphere::Sphere() : radius(1), centre(Vector3()), colour(Colour()) {};
Sphere::Sphere(float radius, Vector3 centre, Colour colour) : radius(radius), centre(centre), colour(colour) {};

Colour Sphere::getColour() {
	return colour;
}

rayIntersection Sphere::rayHit(Ray ray) {
	float lineDirectionNorm = ray.direction.length_squared();
	float discriminant = std::pow(dot(ray.direction, ray.origin - centre), 2)
		-  ( lineDirectionNorm * ((ray.origin - centre).length_squared() - radius * radius));
	if (discriminant > 0) {
		//std::cout << "Sphere hit \n";
		const float t = (-(dot(ray.direction, (ray.origin - centre))) - std::sqrt(discriminant)) * (1.0f/lineDirectionNorm);
		return rayIntersection{ true, t };
	} else	return rayIntersection{ false,  -INFINITY };
}

Vector3 Sphere::surfaceNormal(Vector3 pointOnSurface) {
	Vector3 normal = normalise((pointOnSurface - centre));
	return normal;
}

Vector3 Plane::surfaceNormal(Vector3 pointOnSurface) {
	return normalise(normal);
}