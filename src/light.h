#pragma once
#include "math/geometry.h"

class Light {
public:
	float intensity;
	Light();
	Light(float intensity);
};

class DirectionalLight : public Light{
public:
	Vector3 direction;

	DirectionalLight();
	DirectionalLight(float intensity, Vector3 direction);
};

class PointLight : public Light {
public:
	Vector3 location;

	PointLight();
	PointLight(float intensity, Vector3 location);
	Vector3 rayFromLightToPoint(Vector3 point);
	Vector3 rayFromPointToLight(Vector3 point);
};