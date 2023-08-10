#include "Grid_Edges.h"

Grid_Edges::Grid_Edges(int num_cols, int num_rows, double cell_size)
    : Grid_Base(num_cols, num_rows, cell_size),
      edges_tileX(numcells, edgetypes::EMPTY),
      edges_tileY(numcells, edgetypes::EMPTY),
      edges_doorX(numcells, 0),
      edges_doorY(numcells, 0) {}

void Grid_Edges::Clear() {
    for (int i = 0; i < numcells; i++) {
        edges_tileX[i] = edgetypes::EMPTY;
        edges_tileY[i] = edgetypes::EMPTY;
        edges_doorX[i] = 0;
        edges_doorY[i] = 0;
    }
}

void Grid_Edges::Debug_Draw(SimpleRenderer& rend) {
    for (int u = 0; u < numcols; u++) {
        for (int v = 0; v < numrows; v++) {
            double halfwidth = cellsize * 0.5;
            int index = GetCellIndexFromGridspacePosition(u, v);
            vec2 cellpos = DEBUG_GetWorldspaceCellCenterPositionFromIndex(index);

            if (edges_tileX[index] != edgetypes::EMPTY) {
                if (edges_tileX[index] == edgetypes::PARTIAL) {
                    //rend.SetStyle(0, 0xAAAAAA, 100);
                } else {
                    //rend.SetStyle(0, 0x222222, 100);
                }
                //rend.DrawLine(cellpos.x + halfwidth - 2, cellpos.y - halfwidth + 2, cellpos.x + halfwidth - 2, cellpos.y + halfwidth - 2);
            }
            if (edges_tileY[index] != edgetypes::EMPTY) {
                if (edges_tileY[index] == edgetypes::PARTIAL) {
                    //rend.SetStyle(0, 0xAAAAAA, 100);
                } else {
                    //rend.SetStyle(0, 0x222222, 100);
                }
                //rend.DrawLine(cellpos.x - halfwidth + 2, cellpos.y + halfwidth - 2, cellpos.x + halfwidth - 2, cellpos.y + halfwidth - 2);
            }

            //rend.SetStyle(0, 0x228822, 100);
            if (edges_doorX[index] != 0) {
                //rend.DrawAABB(cellpos.x + halfwidth - 2, cellpos.x + halfwidth + 2, cellpos.y - halfwidth + 2, cellpos.y + halfwidth - 2);
            }
            if (edges_doorY[index] != 0) {
                //rend.DrawAABB(cellpos.x - halfwidth + 2, cellpos.x + halfwidth - 2, cellpos.y + halfwidth - 2, cellpos.y + halfwidth + 2);
            }
        }
    }
}

int Grid_Edges::DOOR_GetCellIndexFromGridspacePosition(int u, int v) {
    return GetCellIndexFromGridspacePosition(u, v);
}

int Grid_Edges::GetGridCoordinateFromWorldspace_1D(double world_coord) {
    return WorldspaceToGridspace(world_coord);
}

int Grid_Edges::GetWorldspaceCoordinateFromGridEdge_1D(int grid_coord, int dir) {
    return ((grid_coord + max(0, dir)) * cellsize);
}

bool Grid_Edges::IsSolid(int u, int v, int dir_u, int dir_v) {
    int index = GetIndexFromGridspaceAndOffset(u, v, dir_u, dir_v);
    if (dir_v == 0) {
        return (edges_tileX[index] == edgetypes::SOLID || edges_doorX[index] != 0);
    } else {
        return (edges_tileY[index] == edgetypes::SOLID || edges_doorY[index] != 0);
    }
}

bool Grid_Edges::IsSolid_IgnoreDoors(int u, int v, int dir_u, int dir_v) {
    int index = GetIndexFromGridspaceAndOffset(u, v, dir_u, dir_v);	
    if (dir_v == 0) {
        return (edges_tileX[index] == edgetypes::SOLID);
    } else {
        return (edges_tileY[index] == edgetypes::SOLID);
    }
}

bool Grid_Edges::IsEmpty(int u, int v, int dir_u, int dir_v) {
    int index = GetIndexFromGridspaceAndOffset(u, v, dir_u, dir_v);
    if (dir_v == 0) {
        return (edges_tileX[index] == edgetypes::EMPTY && edges_doorX[index] == 0);
    } else {
        return (edges_tileY[index] == edgetypes::EMPTY && edges_doorY[index] == 0);
    }
}

bool Grid_Edges::ScanHorizontal(int min_v, int max_v, int start_u, int end_u) {
    int du = end_u - start_u;
    if (du != 0) {
        int dir_u = du / std::abs(du);
        return ScanHorizontal_Directed(min_v, max_v, start_u, end_u, dir_u);
    }
    return true;
}

bool Grid_Edges::ScanHorizontal_Directed(int min_v, int max_v, int start_u, int end_u, int dir_u) {
    int u = start_u;
    while (u != end_u) {
        if (!IsEmpty_Column(u, min_v, max_v, dir_u)) {
            return false;
        }
        u += dir_u;
        if (abs(u) > 100) {
            return false;
        }
    }
    return true;
}

bool Grid_Edges::ScanVertical(int min_u, int max_u, int start_v, int end_v) {
    int dv = end_v - start_v;
    if (dv != 0) {
        int dir_v = dv / std::abs(dv);
        return ScanVertical_Directed(min_u, max_u, start_v, end_v, dir_v);
    }
    return true;
}

bool Grid_Edges::ScanVertical_Directed(int min_u, int max_u, int start_v, int end_v, int dir_v) {
    int v = start_v;
    while (v != end_v) {
        if (!IsEmpty_Row(v, min_u, max_u, dir_v)) {
            return false;
        }
        v += dir_v;
        if (abs(v) > 100) {
            return false;
        }
    }
    return true;
}

int Grid_Edges::SweepHorizontal(int min_v, int max_v, int start_u, int dir) {
    int u = start_u;
    while (true) {
        if (!IsEmpty_Column(u, min_v, max_v, dir)) {
            break;
        }
        u += dir;
        if (abs(u) > 100) {
            return start_u;
        }
    }
    return u;
}

int Grid_Edges::SweepVertical(int min_u, int max_u, int start_v, int dir) {
    int v = start_v;
    while (true) {
        if (!IsEmpty_Row(v, min_u, max_u, dir)) {
            break;
        }
        v += dir;
        if (abs(v) > 100) {
            return start_v;
        }
    }
    return v;
}

bool Grid_Edges::IsEmpty_Column(int u, int min_v, int max_v, int dir) {
    for (int v = min_v; v <= max_v; v++) {
        if (!IsEmpty(u, v, dir, 0)) {
            return false;
        }
    }
    return true;
}

bool Grid_Edges::IsEmpty_Row(int v, int min_u, int max_u, int dir) {
    for (int u = min_u; u <= max_u; u++) {
        if (!IsEmpty(u, v, 0, dir)) {
            return false;
        }
    }
    return true;
}

void Grid_Edges::GAME_LoadTileEdges(int tile_u, int tile_v, int tileID) {
    int origin_u = tile_u * 2;
    int origin_v = tile_v * 2;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            int Xu = origin_u - 1 + i;
            int Xv = origin_v + j;

            int Yu = origin_u + j;
            int Yv = origin_v - 1 + i;

            int Xid = GetCellIndexFromGridspacePosition(Xu, Xv);
            int Yid = GetCellIndexFromGridspacePosition(Yu, Yv);

            int offset = i + (j * 3);

            LoadEdgeState_X(Xid, edgedefs::GetEdgeState_X(tileID, offset));
            LoadEdgeState_Y(Yid, edgedefs::GetEdgeState_Y(tileID, offset));
        }
    }
}

void Grid_Edges::DOOR_IncrementEdge(int cell_index, bool isHorizontal) {
    if (cell_index < 0 || cell_index >= numcells) {
        return;
    }
    if (isHorizontal) {
        edges_doorX[cell_index] += 1;
    } else {
        edges_doorY[cell_index] += 1;
    }
}

void Grid_Edges::DOOR_DecrementEdge(int cell_index, bool isHorizontal) {
    if (cell_index < 0 || cell_index >= numcells) {
        return;
    }
    if (isHorizontal) {
        if (edges_doorX[cell_index] <= 0) {
            return;
        }
        edges_doorX[cell_index] -= 1;
    } else {
        if (edges_doorY[cell_index] <= 0) {
            return;
        }
        edges_doorY[cell_index] -= 1;
    }
}

int Grid_Edges::GetIndexFromGridspaceAndOffset(int u, int v, int dir_u, int dir_v) {
    int index = -1;
    if (dir_v == 0) {
        if (dir_u == -1) {
            index = GetCellIndexFromGridspacePosition(u - 1, v);
        } else if (dir_u == 1) {
            index = GetCellIndexFromGridspacePosition(u, v);
        }
    } else if (dir_u == 0) {
        if (dir_v == -1) {
            index = GetCellIndexFromGridspacePosition(u, v - 1);
        } else if (dir_v == 1) {
            index = GetCellIndexFromGridspacePosition(u, v);
        }
    }
    return index;
}

void Grid_Edges::LoadEdgeState_X(int index, int edgestate) {
    if (edges_tileX[index] == edgetypes::SOLID && edgestate == edgetypes::SOLID) {
        edges_tileX[index] = edgetypes::EMPTY;
    } else {
        edges_tileX[index] = max(edges_tileX[index], edgestate);
    }
}

void Grid_Edges::LoadEdgeState_Y(int index, int edgestate) {
    if (edges_tileY[index] == edgetypes::SOLID && edgestate == edgetypes::SOLID) {
        edges_tileY[index] = edgetypes::EMPTY;
    } else {
        edges_tileY[index] = max(edges_tileY[index], edgestate);
    }
}

void Grid_Edges::SetDoorState_X(int index, int edgestate) {
    edges_doorX[index] = edgestate;
}

void Grid_Edges::SetDoorState_Y(int index, int edgestate) {
    edges_doorY[index] = edgestate;
}