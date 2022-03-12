#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <cmath>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <ppl.h>

#include "utility/utility.h"
#include "math/geometry.h"
#include "math/vector3.h"
#include "math/plane.h"
#include "math/sphere.h"
#include "math/triangle.h"
#include "utility/camera.h"
#include "physics/light.h"
#include "raytrace.h"
#include "utility/scene.h"

constexpr int maxNumberOfRays = 4;
constexpr int resolution = 500;
constexpr int aspectRatioWidth = 3;
constexpr int aspectRatioHeight = 2;

constexpr int horizontalResolution = resolution * aspectRatioWidth;
constexpr int verticalResolution = resolution * aspectRatioHeight;

void threadFunction(int maxNumberOfRays, Scene* scene, float deltaX, float deltaY, int x, int y, PPM (*image)[horizontalResolution]) {
	Vector3 viewVector = scene->camera.upperLeftCorner + Vector3(deltaX * x, -deltaY * y, -1);
	Ray ray = Ray(scene->camera.cameraLocation, viewVector);

	Colour illuminatedColour = raytrace(ray, &maxNumberOfRays, scene);

	Colour tonemapped = reinhardTonemap(illuminatedColour);
	//std::cout << "Original: " <<std::to_string(illuminatedColour.red) << "\n";
	//std::cout << "Tonemapped: " << std::to_string(tonemapped.red) << "\n";

	// Convert to pixel coordinates
	image[y][x].red = 255 * tonemapped.red;
	image[y][x].green = 255 * tonemapped.green;
	image[y][x].blue = 255 * tonemapped.blue;
}

int main() {

	auto mainBegin = std::chrono::system_clock::now();

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
	Plane leftRedWall = Plane(Vector3(1, 0, 0), Vector3(-10, 0, 0), { 0.7f, 0.0f, 0.0f }, {0.01f, 0.01f, 0.01f});
	//Plane leftMirrorWall = Plane(Vector3(1, 0, 0), Vector3(-10, 0, 0), { 0.0f, 0.0f, 0.0f }, { 0.4f, 0.4f, 0.4f }, true);

	Plane backMirrorWall = Plane(Vector3(0, 0, 1), Vector3(1, 0, -30), { 0.0f, 0.0f, 0 }, { 0.9f, 0.9f, 0.9f }, true);

	Plane backdarkGreenWall = Plane(Vector3(0, 0, 1), Vector3(1, 0, -30), { 0.05f, 0.1f, 0 }, {0, 0, 0});
	Plane rightBlueWall = Plane(Vector3(-1, 0, 0), Vector3(10, 0, 0), { 0, 0, 0.8f }, {0.2f, 0.2f, 0.2f});
	//Plane purpleFloor = Plane(Vector3(0, 1, 0), Vector3(0, -5, 0), { 0.29f, 0.0f, 0.50f }, {0, 0, 0});
	Plane greyCeiling = Plane(Vector3(0, -1, 0), Vector3(0, 5, 0), { 0.78f, 0.78f, 0.78f }, {0, 0, 0});
	Plane greenFloor = Plane(Vector3(0, 1, 0), Vector3(0, -5, 0), { 0.05f, 0.1f, 0.0f }, { 0, 0, 0 });

	//Spheres
	Sphere glassSphere = Sphere(1.3, Vector3(-1, -2, -11), { 0.0f, 0.0f, 0 }, { 0.0f, 0.0f, 0.0f }, {0.8f, 0.8f, 0.8f}, 1.3f);
	Sphere lightGreenSphere = Sphere(1.5, Vector3(4, 0, -13), { 0, 0.6f, 0.04f }, { 0.4f, 0.4f, 0.4f });
	Sphere pinkSphere = Sphere(0.5, Vector3(-4, 3, -20), { 0.78f, 0.0f, 0.6f }, {0.03f, 0.03f, 0.03f});

	//Triangles
	Triangle firstTriangle = Triangle(Vector3(-10, 0, -20), Vector3(-5, 0, -20), Vector3(-6, 2, -20), Vector3(0, 0, 1), { 0.2f, 0.9f, 0.75f }, { 0.0f, 0.0f, 0.0f });

	Surface* objects[] = { &leftRedWall, &backMirrorWall, &rightBlueWall, &greenFloor, &greyCeiling, &glassSphere,  &lightGreenSphere, &pinkSphere, &firstTriangle };
	//Surface* objects[] = { &backMirrorWall, &leftRedWall,&greyCeiling, &rightBlueWall, &greenFloor };
	//Surface* objects[] = { &firstTriangle};
	const size_t numberOfObjects = std::size(objects);

	//Lights
	//DirectionalLight directionalLight = DirectionalLight({1, 1, 1}, Vector3(10, -1, 0));
	PointLight ceilingLight = PointLight({1.0f, 1.0f, 1.5f}, 2.0f, Vector3(0, 3, -18));
	PointLight floorLight = PointLight({1.0f, 1.0f, 1.0f}, 0.8f, Vector3(0, -3, -10));

	PointLight* PointLights[] = { &ceilingLight };
	const size_t numberOfLights = std::size(PointLights);

	Scene* scene = new Scene{objects, numberOfObjects, PointLights, numberOfLights, camera};
	//TODO Change to open MPI
	concurrency::parallel_for(0, verticalResolution, [&](int y) {
		for (int x = 0; x < horizontalResolution; x++) {
			threadFunction(maxNumberOfRays, scene, deltaX, deltaY, x, y, image);
		}
	});
	auto renderEnd = std::chrono::system_clock::now();
	std::cout << "Rendering time is: " << std::chrono::duration_cast<std::chrono::milliseconds>(renderEnd - mainBegin).count() << "ms" << std::endl;
	stbi_write_png("../../../outputImage.png", horizontalResolution, verticalResolution, 3, image, horizontalResolution * sizeof(PPM));
	delete[] image;
	return 0;
}
