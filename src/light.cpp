#include "light.h"

Light::Light() : colour{Colour()} {}
Light::Light(Colour colour) : colour{colour}{}

DirectionalLight::DirectionalLight() {
	colour = Colour();
	direction = Vector3();
}

DirectionalLight::DirectionalLight(Colour colour, Vector3 direction) : Light(colour), direction{ direction } {}


PointLight::PointLight() {
	colour = Colour();
	location = Vector3();
}

PointLight::PointLight(Colour colour,Vector3 location) : Light(colour), location{ location } {}


Vector3 PointLight::rayFromLightToPoint(Vector3 point) {
	return point - location;
}

Vector3 PointLight::rayFromPointToLight(Vector3 point) {
	return location - point;
}
