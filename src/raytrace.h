#pragma once
#include "math/geometry.h"
#include "trace.h"
#include "physics/shade.h"
#include "utility/utility.h"

Colour  raytrace(Ray ray, PointLight** lights, size_t numberOfLights, Surface** objects, size_t numberOfObjects);