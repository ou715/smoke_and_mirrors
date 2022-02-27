#pragma once

struct PPM {
	unsigned char red = 0;
	unsigned char green = 0;
	unsigned char blue = 0;
};

PPM transpose(PPM image, int n, int m);

/*
 * Will add other colour representations in the future
 */
class Colour {
public:
	int red, green, blue;
	Colour();
	Colour(int r, int g, int b);

	Colour operator+(Colour otherColour);
	Colour operator-(Colour otherColour);
	Colour operator*(float lightIntensity);
};

int clamp(float c);