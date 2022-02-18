// smoke_and_mirrors.cpp : Defines the entry point for the application.
//
#include "smoke_and_mirrors.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include <fstream>
#include <chrono>

#include "utility.h"


using namespace std;

int main(){

	auto mainBegin = std::chrono::system_clock::now();

	const int x_max = 600;
	const int y_max = 400;

	Colour pixelColour;

	auto image = new PPM[y_max][x_max];

	Camera camera = Camera(Vector3(0, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, -1), 1.5, 1);


	Plane leftRedWall = Plane(Vector3(-5, 0,0), Vector3(-5, 0, 0), Colour(255, 0, 0));
	Plane backGreenWall = Plane(Vector3(0, 0, -1), Vector3(1, 0 , -20), Colour(0, 255, 0));
	Plane rightBlueWall = Plane(Vector3(5, 0, 0), Vector3(5, 0, 0), Colour(0, 0, 255));
	Plane purpleFloor = Plane(Vector3(0, -1, 0), Vector3(0, -10, 0), Colour(75, 0, 130));
	Plane whiteCeiling = Plane(Vector3(0, 1, 0), Vector3(0, 10, 0), Colour(255, 255, 255));
	

	float deltaX = camera.horizontal / x_max;
	float deltaY = camera.vertical / y_max;
	std::cout << std::to_string(camera.upperLeftCorner.x) + " y: ";
	std::cout << std::to_string(camera.upperLeftCorner.y) + " z: ";
	std::cout << std::to_string(camera.upperLeftCorner.z) + "\n";

	/*
	 * Convert format for stbi
	 */
	for (int y = 0; y < y_max; y++) {
		for (int x = 0; x < x_max; x++) {

			Vector3 viewVector = camera.upperLeftCorner + Vector3(deltaX * x, -deltaY * y, 0);

			Ray ray = Ray(viewVector, camera.cameraLocation );

			std::vector<rayIntersection> listOfObjects, listOfIntersectedObjects;

			rayIntersection redWallIntersection = leftRedWall.rayHit(ray);
			rayIntersection blueWallIntersection = rightBlueWall.rayHit(ray);
			rayIntersection greenWallIntersection = backGreenWall.rayHit(ray);
			rayIntersection purpleFloorIntersection = purpleFloor.rayHit(ray);
			rayIntersection whiteCeilingIntersection = whiteCeiling.rayHit(ray);

			listOfObjects.push_back(redWallIntersection);
			listOfObjects.push_back(greenWallIntersection);
			listOfObjects.push_back(blueWallIntersection);
			listOfObjects.push_back(purpleFloorIntersection);
			listOfObjects.push_back(whiteCeilingIntersection);

			//Filter out the objects behind the camera and not intersecting with rays


			std::copy_if(listOfObjects.begin(), listOfObjects.end(), std::back_inserter(listOfIntersectedObjects), [](rayIntersection rayIntersection) {return rayIntersection.t > 0 && rayIntersection.intersected; });
			std::sort(listOfIntersectedObjects.begin(), listOfIntersectedObjects.end(), compareRayIntersectionsByZ);

			image[y][x].red = listOfIntersectedObjects.begin()->colour.red;
			image[y][x].green = listOfIntersectedObjects.begin()->colour.green;
			image[y][x].blue = listOfIntersectedObjects.begin()->colour.blue;
		}
	}
	auto renderEnd = std::chrono::system_clock::now();
	std::cout << "Rendering time is: " << std::chrono::duration_cast<std::chrono::milliseconds>(renderEnd - mainBegin).count() << "ms" << std::endl;
	stbi_write_png("image.png", x_max, y_max, 3, image, x_max * sizeof(PPM));
	delete[] image;
	return 0;
}
