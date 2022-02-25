// smoke_and_mirrors.cpp : Defines the entry point for the application.
//
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <cmath>
#include <iostream>
#include <string>
#include <chrono>

#include "utility.h"
#include "geometry.h"
#include "camera.h"
#include "light.h"
#include "trace.h"
#include "shade.h"

using namespace std;

int main(){

	auto mainBegin = std::chrono::system_clock::now();

	const int resolution = 200;
	const int aspectRatioWidth = 3;
	const int aspectRatioHeight = 2;

	const int horizontalResolution = resolution * aspectRatioWidth;
	const int verticalResolution = resolution * aspectRatioHeight;
	auto image = new PPM[verticalResolution][horizontalResolution];

	const float viewportWidth = 3;
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

	Colour backgroundColour = Colour();

	//Planes TODO convert to rectangles/triangle meshes
	Plane leftRedWall = Plane(Vector3(1, 0,0), Vector3(-10, 0, 0), Colour(255, 60, 60));
	Plane backdarkGreenWall = Plane(Vector3(0, 0, 1), Vector3(1, 0 , -30), Colour(0, 50, 0));
	Plane rightBlueWall = Plane(Vector3(-1, 0, 0), Vector3(10, 0, 0), Colour(0, 0, 255));
	Plane purpleFloor = Plane(Vector3(0, 1, 0), Vector3(0, -5, 0), Colour(75, 0, 130));
	Plane greyCeiling = Plane(Vector3(0, -1, 0), Vector3(0, 5, 0), Colour(200, 200, 200));

	//Spheres
	Sphere yellowSphere = Sphere(1, Vector3(-8, 1, -15), Colour(255, 255, 0));
	Sphere lightGreenSphere = Sphere(1.5, Vector3(4, 2, -18), Colour(0, 240, 1));

	Object* objects[] = { &leftRedWall, &backdarkGreenWall, &rightBlueWall, &purpleFloor, &greyCeiling, &yellowSphere,  &lightGreenSphere };
	//Object* objects[] = {  &lightGreenSphere };
	//Object* objects[] = { &backdarkGreenWall };
	//Object* objects[] = { &rightBlueWall, &lightGreenSphere };
	const size_t numberOfObjects = std::size(objects);

	//Lights
	DirectionalLight directionalLight = DirectionalLight(1, Vector3(10, -1, 0));
	PointLight ceilingLight = PointLight(0.7f, Vector3(0, 3, -15));

	PointLight* PointLights[] = { &ceilingLight };
	const size_t numberOfLights = std::size(PointLights);

	for (int y = 0; y < verticalResolution; y++) {
		for (int x = 0; x < horizontalResolution; x++) {
			Vector3 viewVector = camera.upperLeftCorner + Vector3(deltaX * x, -deltaY * y, -1);

			Ray ray = Ray( camera.cameraLocation, viewVector);

			Colour illuminatedColour = backgroundColour;
			Path tracedPath = trace(objects, ray, numberOfObjects, 1, INFINITY);

			if (tracedPath.firstIntersection.intersected) {
				illuminatedColour = shade(tracedPath, ray, PointLights, numberOfLights, objects, numberOfObjects);
			}

			// Convert to pixel coordinates
			image[y][x].red = illuminatedColour.red;
			image[y][x].green = illuminatedColour.green;
			image[y][x].blue = illuminatedColour.blue;
		}
	}
	auto renderEnd = std::chrono::system_clock::now();
	std::cout << "Rendering time is: " << std::chrono::duration_cast<std::chrono::milliseconds>(renderEnd - mainBegin).count() << "ms" << std::endl;
	stbi_write_png("../../../outputImage.png", horizontalResolution, verticalResolution, 3, image, horizontalResolution * sizeof(PPM));
	delete[] image;
	return 0;
}
