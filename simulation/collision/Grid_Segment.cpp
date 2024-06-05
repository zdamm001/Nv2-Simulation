#include "Grid_Segment.h"

Grid_Segment::Grid_Segment(int num_cols, int num_rows, double cell_size)
    : Grid_Base(num_cols, num_rows, cell_size), cells(numcells, vector<Segment*>()) {
    TEMP_ray_pos = vec2();
    TEMP_ray_vec = vec2();
    TEMP_temp_p = vec2();
    TEMP_temp_n = vec2();
}

Grid_Segment::Grid_Segment(int num_cols, int num_rows, double cell_size, vector<vector<Segment*>> cells)
    : Grid_Base(num_cols, num_rows, cell_size), cells(cells) {
    TEMP_ray_pos = vec2();
    TEMP_ray_vec = vec2();
    TEMP_temp_p = vec2();
    TEMP_temp_n = vec2();
}

void Grid_Segment::DEBUG_Draw(SimpleRenderer& rend) {
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            cells[i][j]->DebugDraw(rend);
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

bool Grid_Segment::RaycastVsPlayer(const vec2& query_pos, const vec2& player_pos, double player_r, vec2& hit_pos, vec2& hit_n) {
    double dir_to_player_X = player_pos.x - query_pos.x;
    double dir_to_player_Y = player_pos.y - query_pos.y;
    
    double dist_to_player = sqrt(dir_to_player_X * dir_to_player_X + dir_to_player_Y * dir_to_player_Y);
    
    if (dist_to_player < player_r) {
        return true;
    }
    
    dir_to_player_X /= dist_to_player;
    dir_to_player_Y /= dist_to_player;
        
    dist_to_player -= player_r;
        
    double hit_dist = GetRaycastDistance(query_pos.x, query_pos.y, dir_to_player_X, dir_to_player_Y, hit_pos, hit_n);
    
    if (dist_to_player < hit_dist) {
        return true;
    }
    
    if (hit_dist == -1) {
        hit_pos.x = 0;
        hit_pos.y = 0;
        hit_n.x = 1;
        hit_n.y = 0;
    }
    
    return false;
}

double Grid_Segment::IntersectRayVsCellContents(int u, int v, const vec2& ray_pos, const vec2& ray_vec, vec2& out_pos, vec2& out_normal) {
    double best_t = 2;
    vec2 TEMP_temp_p;
    vec2 TEMP_temp_n;
    
    TEMP_temp_p.x = 0;
    TEMP_temp_p.y = 0;
    TEMP_temp_n.x = 0;
    TEMP_temp_n.y = 0;
    
    int index = GetCellIndexFromGridspacePosition(u, v);
    const vector<Segment*>& segList = cells[index];
    
    for (size_t i = 0; i < segList.size(); i++) {
        Segment* seg = segList[i];
        double curr_t = seg->IntersectWithRay(ray_pos, ray_vec, 0, TEMP_temp_p, TEMP_temp_n);
        
        if (curr_t == -1) {
            return -1;
        } else if (curr_t < best_t) {
            best_t = curr_t;
            out_pos.Copy(TEMP_temp_p);
            out_normal.Copy(TEMP_temp_n);
        }
    }
    
    return best_t;
}

vector<Segment*> Grid_Segment::DEBUG_GetCellContentsFromGridspacePosition(int u, int v) {
    int index = GetCellIndexFromGridspacePosition(u, v);
    return cells[index];
}

void Grid_Segment::Clear() {
    for (int i = 0; i < numcells; i++) {
        vector<Segment*>& cell = cells[i];
        for (Segment* seg : cell) {
            delete seg;
        }
        cell.clear();
    }
}

void Grid_Segment::AddSegToCell(int cell_u, int cell_v, Segment* seg) {
    int index = GetCellIndexFromGridspacePosition(cell_u, cell_v);
    if (index < 0 || index >= cells.size()) {
        return;
    }
    cells[index].push_back(seg);
}

void Grid_Segment::DOOR_AddSegment(int cell_index, Segment* seg) {
    if (cell_index < 0 || cell_index >= numcells) {
        return;
    }
    vector<Segment*>& cell = cells[cell_index];
    if (find(cell.begin(), cell.end(), seg) != cell.end()) {
        return;
    }
    cells[cell_index].push_back(seg);
}

void Grid_Segment::DOOR_RemoveSegment(int cell_index, Segment* seg) {
    if (cell_index < 0 || cell_index >= numcells) {
        return;
    }
    vector<Segment*>& cell = cells[cell_index];
    vector<Segment*>::iterator it = find(cell.begin(), cell.end(), seg);
    if (it == cell.end()) {
        return;
    }
    cell.erase(it);
}

int Grid_Segment::DOOR_GetCellIndexFromGridspacePosition(int u, int v) {
    return GetCellIndexFromGridspacePosition(u, v);
}

void Grid_Segment::GatherCellContentsFromWorldspaceRegion(double min_x, double min_y, double max_x, double max_y, vector<Segment*>& out_segList) {
    int min_u = WorldspaceToGridspace(min_x);
    int max_u = WorldspaceToGridspace(max_x);
    int min_v = WorldspaceToGridspace(min_y);
    int max_v = WorldspaceToGridspace(max_y);

    out_segList.clear();

    for (int j = min_v; j <= max_v; j++) {
        for (int i = min_u; i <= max_u; i++) {
            int index = GetCellIndexFromGridspacePosition(i, j);
            if (index < 0) {
                //continue;
            }
            vector<Segment*>& cell = cells[index];
            out_segList.insert(out_segList.end(), cell.begin(), cell.end());
        }
    }
}

int Grid_Segment::DOOR_GetSegInnerIndex(int cell_index, Segment* seg) {
    if (cell_index < 0 || cell_index >= numcells) {
        return -1;
    }

    vector<Segment*>& cell = cells[cell_index];
    vector<Segment*>::iterator it = find(cell.begin(), cell.end(), seg);

    if (it == cell.end()) {
        return -1;
    }

    int index = distance(cell.begin(), it);
    return index;
}

Segment* Grid_Segment::DOOR_GetSegment(int cell_index, int seg_index) {
    if (cell_index < 0 || cell_index >= numcells) {
        return nullptr;
    }

    vector<Segment*>& cell = cells[cell_index];

    if (seg_index < 0 || seg_index >= cell.size()) {
        return nullptr;
    }

    return cell[seg_index];
}

Grid_Segment* Grid_Segment::Clone() const {
    vector<vector<Segment*>> clonedCells(numcells);
    
    for (int i = 0; i < numcells; i++) {
        const vector<Segment*>& originalCell = cells[i];
        for (Segment* originalSegment : originalCell) {
            clonedCells[i].push_back(originalSegment->Clone());
        }
    }
    return new Grid_Segment(numcols, numrows, cellsize, clonedCells);
}