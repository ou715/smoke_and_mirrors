#pragma once

#include "../trace.h"
#include "../utility/utility.h"
#include "../math/geometry.h"
#include "light.h"
#include "../shadowTrace.h"
#include <algorithm>

Colour shade(intersectionInformation path, Ray ray, PointLight** lights, size_t numberOfLights, Surface** objects, size_t numberOfObjects);