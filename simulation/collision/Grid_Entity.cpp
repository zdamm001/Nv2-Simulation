#include "Grid_Entity.h"

Grid_Entity::Grid_Entity(int num_cols, int num_rows, double cell_size)
    : Grid_Base(num_cols, num_rows, cell_size), cells(numcells, vector<Entity_Base*>()) {}

void Grid_Entity::Debug_Draw(SimpleRenderer& rend) {
    for (int u = 0; u < numcols; u++) {
        for (int v = 0; v < numrows; v++) {
            vec2 cell_center((0.5 + u) * cellsize, (0.5 + v) * cellsize);
            //rend.SetStyle(0, 0x222288, 100);
            //rend.DrawStringAtPosition(to_string(cells[GetCellIndexFromGridspacePosition(i, j)].size()), cell_center.x, cell_center.y);
        }
    }
}

void Grid_Entity::Clear() {
    for (int i = 0; i < numcells; i++) {
        cells[i].clear();
    }
}

void Grid_Entity::ENTITY_Move(const vec2& new_position, Entity_Base* entity) {
    int curr_index = entity->GRID_GetGridIndex();
    int new_index = GetCellIndexFromWorldspacePosition(new_position.x, new_position.y);
    if (curr_index != new_index) {
        if (curr_index == -1) return;
        RemoveEntityFromCell(curr_index, entity);
        InsertEntityIntoCell(new_index, entity);
        entity->GRID_SetGridIndex(new_index);
    }
}

void Grid_Entity::ENTITY_Remove(Entity_Base* entity) {
    int index = entity->GRID_GetGridIndex();
    if (index == -1) return;
    RemoveEntityFromCell(index, entity);
    entity->GRID_SetGridIndex(-1);
}

void Grid_Entity::ENTITY_Add(const vec2& pos, Entity_Base* entity) {
    int index = entity->GRID_GetGridIndex();
    if (index != -1) return;
    int new_index = GetCellIndexFromWorldspacePosition(pos.x, pos.y);
    InsertEntityIntoCell(new_index, entity);
    entity->GRID_SetGridIndex(new_index);
}

void Grid_Entity::RemoveEntityFromCell(int cell_index, Entity_Base* entity) {
    vector<Entity_Base*>& cell = cells[cell_index];
    auto entity_it = find(cell.begin(), cell.end(), entity);
    if (entity_it == cell.end()) return;
    cell.erase(entity_it);
}

void Grid_Entity::InsertEntityIntoCell(int cell_index, Entity_Base* entity) {
    vector<Entity_Base*>& cell = cells[cell_index];
    cell.push_back(entity);
}

void Grid_Entity::GatherCellContentsInNeighbourhood(vec2 query_pos, vector<Entity_Base*>& out_entList) {
    out_entList.clear();
    int query_u = WorldspaceToGridspace(query_pos.x);
    int query_v = WorldspaceToGridspace(query_pos.y);
    for (int offset_u = -1; offset_u <= 1; ++offset_u) {
        for (int offset_v = -1; offset_v <= 1; ++offset_v) {
            int index = GetCellIndexFromGridspacePosition(query_u + offset_u, query_v + offset_v);
            vector<Entity_Base*>& cell = cells[index];
            for (size_t k = 0; k < cell.size(); ++k) {
                out_entList.push_back(cell[k]);
            }
        }
    }
}