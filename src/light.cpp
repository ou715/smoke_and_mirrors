#include "light.h"

Light::Light() : intensity{0} {}
Light::Light(float intensity) : intensity{intensity}{}

DirectionalLight::DirectionalLight() {
	intensity = 0;
	direction = Vector3();
}

DirectionalLight::DirectionalLight(float intensityInit, Vector3 direction) : Light(intensityInit), direction{ direction } {}


PointLight::PointLight() {
	intensity = 0;
	location = Vector3();
}

PointLight::PointLight(float intensityInit,Vector3 location) : Light(intensityInit), location{ location } {}


Vector3 PointLight::rayFromLightToPoint(Vector3 point) {
	return location - point;
}
