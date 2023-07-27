#include "Simulator.h"

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