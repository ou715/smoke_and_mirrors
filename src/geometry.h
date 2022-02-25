#pragma once

#include <cmath>

#include <iostream>

#include "utility.h"

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


class Ray {
public:
	Vector3 origin;
	Vector3 direction;

	Ray();
	Ray(Vector3 origin, Vector3 direction);

	Vector3 pointOnRay(float t);
};

struct rayIntersection {
	bool intersected = false;
	float t = INFINITY;
};

class Object {
public:
	virtual rayIntersection rayHit(Ray ray) = 0;
	virtual Vector3 surfaceNormal(Vector3 pointOnSurface) = 0;
	virtual Colour getColour() = 0;
};

class Plane : public Object {
public:
	Vector3 normal;
	Vector3 point;
	Colour colour;

	Plane();
	Plane(Vector3 normal, Vector3 point, Colour colour);

	rayIntersection rayHit(Ray ray) override;
	Vector3 surfaceNormal(Vector3 pointOnSurface) override;
	Colour getColour() override;
};

class Sphere : public Object {
public:
	float radius;
	Vector3 centre;
	Colour colour;

	Sphere();
	Sphere(float radius, Vector3 centre, Colour colour);

	rayIntersection rayHit(Ray ray) override;
	Vector3 surfaceNormal(Vector3 pointOnSurface) override;
	Colour getColour() override;
};

struct Path {
	rayIntersection firstIntersection;
	Vector3 firstIntersectionPoint;
	Object* objectHit;
};