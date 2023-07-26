#include <vector>

#include "..\\editor\\edat.cpp"
#include "..\\math\\mathutils.cpp"
#include "..\\math\\vec2.cpp"

using namespace std;

class Entity_Base;
class Grid_Segment {};
class Grid_Edges {};
class Grid_Entity {};
class Ninja;

class Simulator {
    public:
        const int GRID_NUM_COLS = edat::num_cols + 2;
        const int GRID_NUM_ROWS = edat::num_rows + 2;
        const double GRID_CELL_SIZE = 24;
        const double GRID_CELL_HALFWIDTH = GRID_CELL_SIZE / 2;
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
};

Simulator::Simulator(vector<int> tileIDs, Grid_Segment segGrid, Grid_Edges edgeGrid, Grid_Entity objGrid, vector<Entity_Base*> objList, vector<Ninja*> playerList)
    : tileIDs(tileIDs), segGrid(segGrid), edgeGrid(edgeGrid), objGrid(objGrid), objList(objList), playerList(playerList), frame_num(0), num_gold_collected_during_tick(playerList.size(), 0), STATEFLAG_won(false)/*, HACKY_gfx(nullptr), HACKY_sfx(nullptr)*/ {
    mathutils::SetRandomSeed(1);
}