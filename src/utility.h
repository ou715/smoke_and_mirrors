#pragma once

struct PPM {
	unsigned char red = 0;
	unsigned char green = 0;
	unsigned char blue = 0;
};

PPM transpose(PPM image, int n, int m);
/*
 * Values should be 0-1
 */
struct ColourCoefficients {
	float red = 0;
	float green = 0;
	float blue = 0;
};

/*
 * Will add other colour representations in the future
 */
class Colour {
public:
	float red, green, blue;
	Colour();
	Colour(float r, float g, float b);

	Colour operator+(Colour otherColour);
	Colour operator-(Colour otherColour);
	Colour operator*(float lightIntensity);
	Colour operator*(ColourCoefficients colourCoefficients);
	float getIntensity();
};

//int clamp(float c);
ColourCoefficients operator*(ColourCoefficients colourCoefficientsA, ColourCoefficients colourCoefficientsB);

//TODO Should be improved using the white point
Colour reinhardTonemap(Colour colour);