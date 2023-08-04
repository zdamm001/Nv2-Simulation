#include "Grid_Base.h"

Grid_Base::Grid_Base(int num_cols, int num_rows, double cell_size)
    : numcols(num_cols), numrows(num_rows), numcells(num_cols * num_rows), cellsize(cell_size) { }

int Grid_Base::WorldspaceToGridspace(double pos) const {
    return static_cast<int>(pos / cellsize);
}

int Grid_Base::GetCellIndexFromWorldspacePosition(double pos_x, double pos_y) const {
    return GetCellIndexFromGridspacePosition(WorldspaceToGridspace(pos_x), WorldspaceToGridspace(pos_y));
}

int Grid_Base::GetCellIndexFromGridspacePosition(int pos_u, int pos_v) const {
    if (pos_u < 0 || pos_u >= numcols || pos_v < 0 || pos_v >= numrows) {
        pos_u = max(0, min(numcols - 1, pos_u));
        pos_v = max(0, min(numrows - 1, pos_v));
    }
    return (pos_v * numcols) + pos_u;
}

vec2 Grid_Base::DEBUG_GetWorldspaceCellCenterPositionFromIndex(int id) const {
    if (id != -1) {
        int u = id % numcols;
        int v = id / numcols;
        return vec2((u + 0.5) * cellsize, (v + 0.5) * cellsize);
    } else {
        return vec2(0.0, 0.0);
    }
}