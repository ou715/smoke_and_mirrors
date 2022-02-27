#pragma once
#include <cmath>


class Vector3 {
public:
	float x, y, z;
	Vector3();
	Vector3(float xInit, float yInit, float zInit);
	Vector3 operator-();
	Vector3 operator+(Vector3 otherVector);
	Vector3 operator-(Vector3 otherVector);

	float length();
	float length_squared();
};

Vector3 operator*(float c, Vector3 vector);
Vector3 operator*(Vector3 vector, float c);
float dot(Vector3 vector_a, Vector3 vector_b);
Vector3 cross(Vector3 vector_a, Vector3 vector_b);
Vector3 normalise(Vector3 vector);