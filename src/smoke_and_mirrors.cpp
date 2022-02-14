// smoke_and_mirrors.cpp : Defines the entry point for the application.
//
#include "smoke_and_mirrors.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <cmath>

#include "utility.h"


using namespace std;

int main(){

	const int x_max = 800;
	const int y_max = 400;

	Colour pixelColour;

	struct PPM image[y_max][x_max];

	/*
	 * calculate the image
	 */

	/*
	 * Convert to format for stbi
	 */
	for (int y = y_max - 1; y >= 0; y--) {
		for (int x = 0; x < x_max; x++) {

			float r = float(x) / float(x_max);
			float g = float(y_max -1 - y) / float(y_max);
			float b = 0.2;

			pixelColour = Colour((int)(255.99 * r)
				, (int)255.99 * g
				, (int)(255.99) * b);

			image[y][x].red = pixelColour.red;
			image[y][x].green = pixelColour.green;
			image[y][x].blue = pixelColour.blue;

		}
	}

	stbi_write_png("image.png", x_max, y_max, 3, image, x_max * 3);
	return 0;
}
