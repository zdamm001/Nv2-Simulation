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