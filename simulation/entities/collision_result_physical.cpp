#include "collision_result_physical.h"

collision_result_physical::collision_result_physical() {
    Clear();
}

void collision_result_physical::Clear() {
    pen = 0;
    nx = 0;
    ny = 0;
    isHardCollision = true;
}