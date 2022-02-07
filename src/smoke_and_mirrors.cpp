// smoke_and_mirrors.cpp : Defines the entry point for the application.
//
#include "smoke_and_mirrors.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <cmath>

#include "utility.h"


using namespace std;

int main(){

	const int x_max = 200;
	const int y_max = 100;

	struct PPM image[y_max][x_max];

	for (int y = y_max - 1; y >= 0; y--) {
		for (int x = 0; x < x_max; x++) {

			float r = float(x) / float(x_max);
			float g = float(y_max -1 - y) / float(y_max);
			float b = 0.2;
			
			int ir = (int)(255.99 * r);
			int ig = (int)(255.99 * g);
			int ib = (int)(255.99 * b);

			image[y][x].R = ir;
			image[y][x].G = ig;
			image[y][x].B = ib;

		}
	}

	stbi_write_jpg("image.jpg", x_max, y_max, 3, image, 100);
	return 0;
}
