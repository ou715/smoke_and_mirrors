#pragma once
#include "math/geometry.h"
#include "trace.h"
#include "shade.h"
#include "utility.h"

Colour  raytrace(Ray ray, PointLight** lights, size_t numberOfLights, Surface** objects, size_t numberOfObjects);