#pragma once
#include "math/geometry.h"
#include "physics/surface.h"
#include "utility/scene.h"

bool shadowTrace(Ray ray, float tMin, float tMax, Scene* scene);