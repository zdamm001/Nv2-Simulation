#include "AABB.h"

AABB::AABB(double xmin, double ymin, double xmax, double ymax) 
    : min(xmin, ymin), max(xmax, ymax) { }