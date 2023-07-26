#include <vector>

#include "..\\editor\\edat.cpp"
#include "..\\math\\mathutils.cpp"
#include "..\\math\\vec2.cpp"
#include "entities\\Entity_Base.cpp"

using namespace std;

class Grid_Segment {};
class Grid_Edges {};
class Grid_Entity {};
class Ninja {};
class SimpleRenderer;

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
        void Tick(SimpleRenderer* renderer);
};

Simulator::Simulator(vector<int> tileIDs, Grid_Segment segGrid, Grid_Edges edgeGrid, Grid_Entity objGrid, vector<Entity_Base*> objList, vector<Ninja*> playerList)
    : tileIDs(tileIDs), 
      segGrid(segGrid), 
      edgeGrid(edgeGrid), 
      objGrid(objGrid), 
      objList(objList), 
      playerList(playerList), 
      frame_num(0), 
      num_gold_collected_during_tick(playerList.size(), 0), 
      STATEFLAG_won(false) {
      //HACKY_gfx(nullptr)
      //HACKY_sfx(nullptr)
    mathutils::SetRandomSeed(1);
}

void Simulator::Tick(SimpleRenderer* renderer) {
    for (int i = 0; i < num_gold_collected_during_tick.size(); ++i) {
        num_gold_collected_during_tick[i] = 0;
    }
    for (int i = 0; i < objList.size(); ++i) {
        objList[i]->Move(this);
    }
    for (int i = 0; i < objList.size(); ++i) {
        objList[i]->Think(this);
    }
    for (int i = 0; i < playerList.size(); ++i) {
        playerList[i]->Integrate();
        playerList[i]->PreCollision();
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < playerList.size(); ++j) {
            playerList[j]->SolveInternalConstraints();
        }
        for (int j = 0; j < playerList.size(); ++j) {
            playerList[j]->CollideVsObjects(this);
        }
        for (int j = 0; j < playerList.size(); ++j) {
            playerList[j]->CollideVsTiles(this);
        }
    }
    for (int i = 0; i < playerList.size(); ++i) {
        playerList[i]->PostCollision(this);
    }
    for (int i = 0; i < playerList.size(); ++i) {
        playerList[i]->Think(this, frame_num);
    }
    ++frame_num;
}