#pragma once
#include "math/geometry.h"

bool shadowTrace(Surface** objects, Ray ray, size_t numberOfObjects, float tMin, float tMax);