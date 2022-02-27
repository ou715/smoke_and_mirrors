#pragma once
#include "math/geometry.h"

Path trace(Surface** objects, Ray ray, size_t numberOfObjects, float tMin, float tMax);