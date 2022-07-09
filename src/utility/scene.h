#pragma once

#include "camera.h"
#include "../physics/surface.h"
#include "../physics/light.h"
#include "vector"

struct Scene {
	//Surface** objects;
	std::vector<Surface*> objects;
	size_t numberOfObjects = 0;
	PointLight** PointLights;
	size_t numberOfLights = 0;
	Camera camera;
};