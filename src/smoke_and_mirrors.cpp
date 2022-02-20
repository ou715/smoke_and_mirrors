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

	const int resolution = 200;
	const int aspectRatioWidth = 4;
	const int aspectRatioHeight = 4;

	const int horizontalResolution = resolution * aspectRatioWidth;
	const int verticalResolution = resolution * aspectRatioHeight;
	auto image = new PPM[verticalResolution][horizontalResolution];

	const float viewportWidth = 2 ;
	const float viewportHeight = 2;

	float deltaX = viewportWidth / horizontalResolution;
	float deltaY = viewportHeight / verticalResolution;

	Camera camera = Camera(Vector3(0, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, -1), viewportWidth, viewportHeight);

	std::cout << "Camera is at: \n";
	std::cout << std::to_string(camera.cameraLocation.x) + " y: ";
	std::cout << std::to_string(camera.cameraLocation.y) + " z: ";
	std::cout << std::to_string(camera.cameraLocation.z) + "\n";
	std::cout << "Camera is looking at: \n";
	std::cout << std::to_string(camera.viewingDirection.x) + " y: ";
	std::cout << std::to_string(camera.viewingDirection.y) + " z: ";
	std::cout << std::to_string(camera.viewingDirection.z) + "\n";
	std::cout << "Viewport top left corner is at: \n";
	std::cout << std::to_string(camera.upperLeftCorner.x) + " y: ";
	std::cout << std::to_string(camera.upperLeftCorner.y) + " z: ";
	std::cout << std::to_string(camera.upperLeftCorner.z) + "\n";

	//Planes TODO convert to rectangles/triangle meshes
	Plane leftRedWall = Plane(Vector3(-1, 0,0), Vector3(-10, 0, 0), Colour(255, 0, 0));
	Plane backdarkGreenWall = Plane(Vector3(0, 0, -1), Vector3(1, 0 , -20), Colour(0, 50, 0));
	Plane rightBlueWall = Plane(Vector3(1, 0, 0), Vector3(10, 0, 0), Colour(0, 0, 255));
	Plane purpleFloor = Plane(Vector3(0, -1, 0), Vector3(0, -10, 0), Colour(75, 0, 130));
	Plane whiteCeiling = Plane(Vector3(0, 1, 0), Vector3(0, 10, 0), Colour(255, 255, 255));

	//Spheres
	Sphere yellowSphere = Sphere(2, Vector3(-4, -4, -3), Colour(255, 255, 0));
	Sphere lightGreenSphere = Sphere(2, Vector3(5, 3, -10), Colour(0, 240, 0));

	const int numberOfObjects = 7;	
	Object* objects[numberOfObjects] = {&leftRedWall, &backdarkGreenWall, &rightBlueWall, &purpleFloor, &whiteCeiling,  &yellowSphere, &lightGreenSphere};

	for (int y = 0; y < verticalResolution; y++) {
		for (int x = 0; x < horizontalResolution; x++) {

			Vector3 viewVector = camera.upperLeftCorner + Vector3(deltaX * x, -deltaY * y, 0);

			Ray ray = Ray(camera.cameraLocation, normalise(viewVector));
			//std::cout << "**************************************************************************** \n \n";
			//std::cout << "Ray - x: " << std::to_string(ray.parallelTo.x) << " y: " << std::to_string(ray.parallelTo.y) << " z: " << std::to_string(ray.parallelTo.z) << "\n";

			rayIntersection firstIntersection{false, Vector3(), 0, Colour()};

			float distanceToIntersection = INFINITY; // distance is measured in vectors from camera origin to viewport
			for (int o = 0; o < numberOfObjects; o++) {
				rayIntersection rayIntersection = objects[o]->rayHit(ray);
				//std::cout << "Distance to closest intersection: " << distanceToIntersection << "\n";
				//std::cout << "t: " << rayIntersection.t << " z: " << rayIntersection.intersectionPoint.z << "\n";

				if (rayIntersection.intersected && rayIntersection.t > 0 && rayIntersection.t < distanceToIntersection) {
					firstIntersection = rayIntersection;
					distanceToIntersection = firstIntersection.t;
					//std::cout << std::to_string(rayIntersection.intersectionPoint.x) << "y: " << std::to_string(rayIntersection.intersectionPoint.y) << " z: " << std::to_string(rayIntersection.intersectionPoint.z) << "\n";
					//std::cout << "Colour: " << " Red - " << rayIntersection.colour.red << " Green - " << rayIntersection.colour.green << "\n";
				}
			}
			// Convert to pixel coordinates
			image[y][x].red = firstIntersection.colour.red;
			image[y][x].green = firstIntersection.colour.green;
			image[y][x].blue = firstIntersection.colour.blue;
		}
	}
	auto renderEnd = std::chrono::system_clock::now();
	std::cout << "Rendering time is: " << std::chrono::duration_cast<std::chrono::milliseconds>(renderEnd - mainBegin).count() << "ms" << std::endl;
	stbi_write_png("image.png", horizontalResolution, verticalResolution, 3, image, horizontalResolution * sizeof(PPM));
	delete[] image;
	return 0;
}
