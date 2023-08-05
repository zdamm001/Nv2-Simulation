#pragma once
#include <vector>

#include "Grid_Base.h"
#include "Segment.h"

class Grid_Segment : public Grid_Base {
    private:
        vector<vector<Segment>> cells;
        vec2 TEMP_ray_pos;
        vec2 TEMP_ray_vec;
        vec2 TEMP_temp_p;
        vec2 TEMP_temp_n;
    public:
        Grid_Segment(int num_cols, int num_rows, double cell_size);
        void DEBUG_Draw(SimpleRenderer& rend);
        double GetRaycastDistance(double pos_x, double pos_y, double dir_x, double dir_y, vec2& out_pos, vec2& out_normal);
};