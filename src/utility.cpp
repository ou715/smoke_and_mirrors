#include "utility.h"
#include <cmath>
#include <algorithm>

PPM transpose(PPM image, int n, int m){

	return image;
}
/*
 * The default colour is gray.
 */
Colour::Colour() : red{ 100 }, green{ 100 }, blue{ 100 } {}

Colour::Colour(int r, int g, int b) : red{ r }, green{ g }, blue{ b } {}

Colour Colour::operator+(Colour otherColour) {
	return Colour(clamp(this->red + otherColour.red)
		, clamp(this->green + otherColour.green)
		, clamp(this->blue + otherColour.blue));
}
Colour Colour::operator-(Colour otherColour) {
	return Colour(clamp(this->red - otherColour.red)
				, clamp(this->green - otherColour.green)
				, clamp(this->blue - otherColour.blue));
}

int clamp(float c) {
	return static_cast<int>(std::max(0.0f, std::min(255.0f, c)));
}

Colour Colour::operator*(float lightIntensity) {
	return Colour(clamp(red * lightIntensity), clamp(green * lightIntensity), clamp(blue * lightIntensity));
}