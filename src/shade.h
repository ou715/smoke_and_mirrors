#pragma once

#include "trace.h"
#include <iostream>
#include <string>

#include "utility.h"
#include "math/geometry.h"
#include "light.h"

Colour shade(Path path, Ray ray, PointLight** lights, size_t numberOfLights, Surface** objects, size_t numberOfObjects);