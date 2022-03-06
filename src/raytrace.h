#pragma once
#include "math/geometry.h"
#include "trace.h"
#include "physics/shade.h"
#include "utility/utility.h"

Colour raytrace(Ray ray, int* maxRayDepth, Scene* scene, Colour totalLight = Colour(0, 0, 0), ColourCoefficients totalSpecularCoefficients = {1, 1, 1}, int numberOfRays = 1);