#pragma once

class collision_result_logical {
    public:
        double vec_x;
        double vec_y;
    public:
        collision_result_logical();
        void Clear();
};

collision_result_logical::collision_result_logical() {
    Clear();
}

void collision_result_logical::Clear() {
    vec_x = 0;
    vec_y = 0;
}
