#include "Grid_Segment.h"

Grid_Segment::Grid_Segment(int num_cols, int num_rows, double cell_size)
    : Grid_Base(num_cols, num_rows, cell_size) {
    cells.resize(numcells);
    for (int i = 0; i < numcells; i++) {
        cells[i] = vector<Segment>();
    }
    TEMP_ray_pos = vec2();
    TEMP_ray_vec = vec2();
    TEMP_temp_p = vec2();
    TEMP_temp_n = vec2();
}

void Grid_Segment::DEBUG_Draw(SimpleRenderer& rend) {
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            cells[i][j].DebugDraw(rend);
        }
    }
}

double Grid_Segment::GetRaycastDistance(double pos_x, double pos_y, double dir_x, double dir_y, vec2& out_pos, vec2& out_normal) {
    int U = WorldspaceToGridspace(pos_x);
    int V = WorldspaceToGridspace(pos_y);

    int stepU = 0;
    int stepV = 0;
    double tMaxX = 999999;
    double tMaxY = 999999;
    double tDeltaX = 0;
    double tDeltaY = 0;

    if (dir_x < 0) {
        stepU = -1;
        tMaxX = ((U * cellsize) - pos_x) / dir_x;
        tDeltaX = cellsize / -dir_x;
    } else if (dir_x > 0) {
        stepU = 1;
        tMaxX = (((U + 1) * cellsize) - pos_x) / dir_x;
        tDeltaX = cellsize / dir_x;
    }
    if (dir_y < 0) {
        stepV = -1;
        tMaxY = ((V * cellsize) - pos_y) / dir_y;
        tDeltaY = cellsize / -dir_y;
    } else if (dir_y > 0) {
        stepV = 1;
        tMaxY = (((V + 1) * cellsize) - pos_y) / dir_y;
        tDeltaY = cellsize / dir_y;
    }
    if (stepU == 0 && stepV == 0) {
        return -1;
    }
    
    const double HACKY_LEN = 2000;
    vec2 ray_pos(pos_x, pos_y);
    vec2 ray_vec(HACKY_LEN * dir_x, HACKY_LEN * dir_y);
    double hit_t = 2;
    
    while (true) {
        double result = IntersectRayVsCellContents(U, V, ray_pos, ray_vec, out_pos, out_normal);
        if (result == -1) {
            return -1;
        } else if (result != 2) {
            hit_t = result;
            break;
        }
        if (tMaxX < tMaxY) {
            tMaxX += tDeltaX;
            U += stepU;
            if (U < 0 || U >= numcols) {
                return -1;
            }
        } else {
            tMaxY += tDeltaY;
            V += stepV;
            if (V < 0 || V >= numrows) {
                return -1;
            }
        }
    }
    return (hit_t * HACKY_LEN);
}
