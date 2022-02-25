#pragma once
#include "utility.h"
#include "geometry.h"
#include "light.h"
#include <algorithm>
#include "trace.h"
#include <iostream>
#include <string>



Colour shade(Path path, Ray ray, PointLight** lights, size_t numberOfLights, Object** objects, size_t numberOfObjects);
