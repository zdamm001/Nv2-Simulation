#pragma once
#include <vector>

#include "..\\editor\\edat.h"
#include "..\\math\\mathutils.h"
#include "..\\math\\vec2.h"
#include "collision\\Grid_Edges.h"
#include "collision\\Grid_Entity.h"
#include "collision\\Grid_Segment.h"
#include "entities\\Entity_Base.h"
#include "ninja\\Ninja.h"

using namespace std;

class SimpleRenderer;

class Simulator {
    public:
        static const int GRID_NUM_COLS = edat::num_cols + 2;
        static const int GRID_NUM_ROWS = edat::num_rows + 2;
        static const double GRID_CELL_SIZE = 24;
        static const double GRID_CELL_HALFWIDTH = GRID_CELL_SIZE / 2;
    private:
        vector<Entity_Base*> objList;
        vector<int> tileIDs;
    public:
        Grid_Segment segGrid;
        Grid_Edges edgeGrid;
        Grid_Entity objGrid;
        vector<Ninja*> playerList;
    private:
        unsigned int frame_num;
        vector<int> num_gold_collected_during_tick;
        bool STATEFLAG_won;
        //GraphicsManager* HACKY_gfx;
        //SoundManager* HACKY_sfx;
    public:
        Simulator(vector<int> tileIDs, Grid_Segment segGrid, Grid_Edges edgeGrid, Grid_Entity objGrid, vector<Entity_Base*> objList, vector<Ninja*> playerList);
        void Tick(SimpleRenderer* renderer);
};