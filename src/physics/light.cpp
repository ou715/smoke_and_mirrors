#include "light.h"

Light::Light() : colour{Colour()} {}
Light::Light(Colour colour, float intensity) : colour{ colour }, intensity{intensity}{}

DirectionalLight::DirectionalLight() {
	colour = Colour();
	direction = Vector3();
}

DirectionalLight::DirectionalLight(Colour colour, float lightIntensity, Vector3 direction) : Light(colour, lightIntensity), direction{ direction } {}


PointLight::PointLight() {
	colour = Colour();
	location = Vector3();
	intensity = 1.0f;
}

PointLight::PointLight(Colour colour, float lightIntensity, Vector3 location) : Light(colour, lightIntensity), location{ location } {}


Vector3 PointLight::rayFromLightToPoint(Vector3 point) {
	return point - location;
}

Vector3 PointLight::rayFromPointToLight(Vector3 point) {
	return location - point;
}
