#include "utility.h"

PPM transpose(PPM image, int n, int m){

	return image;
}
/*
 * The default colour is gray.
 */
Colour::Colour() : red{ 0.4f }, green{ 0.4f }, blue{ 0.4f } {}

Colour::Colour(float r, float g, float b) : red{ r }, green{ g }, blue{ b } {}

Colour Colour::operator+(Colour otherColour) {
	return Colour(this->red + otherColour.red
		, this->green + otherColour.green
		, this->blue + otherColour.blue);
}
Colour Colour::operator-(Colour otherColour) {
	return Colour(this->red - otherColour.red
				, this->green - otherColour.green
				, this->blue - otherColour.blue);
}

//int clamp(float c) {
//	return static_cast<int>(std::max(0.0f, std::min(255.0f, c)));
//}

Colour Colour::operator*(float lightIntensity) {
	return Colour(red * lightIntensity, green * lightIntensity, blue * lightIntensity);
}

Colour Colour::operator*(ColourCoefficients colourCoefficients) {
	return Colour(colourCoefficients.red * this->red
		, colourCoefficients.green * this->green
		, colourCoefficients.blue * this->blue);
}

ColourCoefficients operator*(ColourCoefficients colourCoefficientsA, ColourCoefficients colourCoefficientsB) {
	return ColourCoefficients{ colourCoefficientsA.red * colourCoefficientsB.red
								   , colourCoefficientsA.green * colourCoefficientsB.green
								   , colourCoefficientsA.blue * colourCoefficientsB.blue };
}


float Colour::getIntensity() {
	return this->red + this->green + this->blue;
}


Colour reinhardTonemap(Colour colour) {
	float red = colour.red / (colour.red + 1);
	float green = colour.green / (colour.green + 1);
	float blue = colour.blue / (colour.blue + 1);
	return Colour(red, green, blue);
}