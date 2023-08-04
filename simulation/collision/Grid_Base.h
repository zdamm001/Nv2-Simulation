#pragma once
#include "..\\..\\math\\vec2.h"

class Grid_Base {
    protected:
        int numcols;
        int numrows;
        int numcells;
        double cellsize;
    public:
        Grid_Base(int num_cols, int num_rows, double cell_size);
    protected:
        virtual int WorldspaceToGridspace(double pos) const final;
        virtual int GetCellIndexFromWorldspacePosition(double pos_x, double pos_y) const final;
        virtual int GetCellIndexFromGridspacePosition(int pos_u, int pos_v) const final;
    public:
        virtual vec2 DEBUG_GetWorldspaceCellCenterPositionFromIndex(int id) const final;
};
