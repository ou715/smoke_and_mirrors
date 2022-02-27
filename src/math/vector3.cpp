#include "vector3.h"


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

Vector3 operator/(Vector3 vector, float c) {
	return Vector3(vector.x / c, vector.y / c, vector.z / c);
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