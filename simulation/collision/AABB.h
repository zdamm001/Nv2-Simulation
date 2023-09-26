#pragma once

#include "..\\..\\math\\vec2.h"

class AABB {
    public:
        vec2 min;
        vec2 max;
    public:
        AABB(double xmin, double ymin, double xmax, double ymax);
};