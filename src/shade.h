#pragma once
#include "utility.h"
#include "geometry.h"
#include "light.h"
#include <algorithm>


Colour shade(Path path, Ray ray, PointLight** lights, size_t numberOfLights);
