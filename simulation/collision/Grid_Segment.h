#pragma once
#include <vector>
#include <algorithm>

#include "Grid_Base.h"
#include "Segment.h"

class Grid_Segment : public Grid_Base {
    private:
        vector<vector<Segment*>> cells;
        vec2 TEMP_ray_pos;
        vec2 TEMP_ray_vec;
        vec2 TEMP_temp_p;
        vec2 TEMP_temp_n;
    public:
        Grid_Segment(int num_cols, int num_rows, double cell_size);
        void DEBUG_Draw(SimpleRenderer& rend);
        double GetRaycastDistance(double pos_x, double pos_y, double dir_x, double dir_y, vec2& out_pos, vec2& out_normal);
        bool RaycastVsPlayer(const vec2& query_pos, const vec2& player_pos, double player_r, vec2& hit_pos, vec2& hit_n);
    private:
        double IntersectRayVsCellContents(int u, int v, const vec2& ray_pos, const vec2& ray_vec, vec2& out_pos, vec2& out_normal);
    public:
        vector<Segment*> DEBUG_GetCellContentsFromGridspacePosition(int u, int v);
        void Clear();
        void AddSegToCell(int cell_u, int cell_v, Segment* seg);
        void DOOR_AddSegment(int cell_index, Segment* seg);
        void DOOR_RemoveSegment(int cell_index, Segment* seg);
        int DOOR_GetCellIndexFromGridspacePosition(int u, int v);
        void GatherCellContentsFromWorldspaceRegion(double min_x, double min_y, double max_x, double max_y, vector<Segment*>& out_segList);
};