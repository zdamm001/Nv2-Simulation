#pragma once

class collision_result_physical {
    public:
        double pen;
        double nx;
        double ny;
        bool isHardCollision;
    public:
        collision_result_physical();
        void Clear();
};

collision_result_physical::collision_result_physical() {
    Clear();
}

void collision_result_physical::Clear() {
    pen = 0;
    nx = 0;
    ny = 0;
    isHardCollision = true;
}