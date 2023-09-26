#pragma once
#include <vector>
#include <algorithm>

#include "..\\..\\math\\vec2.h"
#include "..\\entities\\Entity_Base.h"
#include "Grid_Base.h"

using namespace std;

class Grid_Entity : public Grid_Base {
    private:
        vector<vector<Entity_Base*>> cells;
    public:
        Grid_Entity(int num_cols, int num_rows, double cell_size);
        void Debug_Draw(SimpleRenderer& rend);
        void Clear();
        void ENTITY_Move(const vec2& new_position, Entity_Base* entity);
        void ENTITY_Remove(Entity_Base* entity);
        void ENTITY_Add(const vec2& pos, Entity_Base* entity);
    private:
        void RemoveEntityFromCell(int cell_index, Entity_Base* entity);
        void InsertEntityIntoCell(int cell_index, Entity_Base* entity);
    public:
        void GatherCellContentsInNeighbourhood(vec2 query_pos, vector<Entity_Base*>& out_entList);
};