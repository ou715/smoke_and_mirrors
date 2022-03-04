#pragma once

#include "../trace.h"
#include "../utility/utility.h"
#include "../math/geometry.h"
#include "light.h"
#include "../shadowTrace.h"
#include <algorithm>
#include "surface.h"
#include "../utility/scene.h"

Colour shade(intersectionInformation path, Ray ray, Scene* scene);