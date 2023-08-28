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
      STATEFLAG_won(false),
      HACKY_gfx(nullptr),
      HACKY_sfx(nullptr) {
    mathutils::SetRandomSeed(1);
}

void Simulator::HACKY_SetAV(GraphicsManager* gfx, SoundManager* sfx) {
    this->HACKY_gfx = gfx;
    this->HACKY_sfx = sfx;
}

ParticleManager* Simulator::HACKY_GetParticleManager() {
    //return this->HACKY_gfx->GetParticleManager();
}

SoundManager* Simulator::HACKY_GetSoundManager() {
    return this->HACKY_sfx;
}

vector<Entity_Base*> Simulator::GFX_GetEntityList() {
    return this->objList;
}

vector<Ninja*> Simulator::GFX_GetPlayerList() {
    return this->playerList;
}

vector<int> Simulator::GFX_GetTileIDs() {
    return this->tileIDs;
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

void Simulator::InternalEvent_KillPlayer(Ninja* ninja, int enemyType, double deathPosX, double deathPosY, double deathForceX, double deathForceY) {
    if (ninja->SIM_Kill(enemyType, deathPosX, deathPosY, deathForceX, deathForceY)) {
        // ...
    }
}

void Simulator::Event_Launchpad_HitPlayer(Ninja* ninja, double launchForceX, double launchForceY) {
    ninja->SIM_Launch(launchForceX, launchForceY);
}

void Simulator::Event_Exit_HitPlayer(Ninja* ninja) {
    STATEFLAG_won = true;
    for (int i = 0; i < playerList.size(); ++i) {
        playerList[i]->SIM_Win();
    }
}

bool Simulator::Event_Gold_HitPlayer(Ninja* ninja) {
    if (!STATEFLAG_won) {
        ++num_gold_collected_during_tick[ninja->GetIndex()];
        return true;
    }
    return false;
}

void Simulator::Event_PlayerWasKilled(Ninja* ninja, int enemyType, double deathPosX, double deathPosY, double deathForceX, double deathForceY) {
    InternalEvent_KillPlayer(ninja, enemyType, deathPosX, deathPosY, deathForceX, deathForceY);
}

bool Simulator::AreAllPlayersDead() {
    for (int i = 0; i < playerList.size(); ++i) {
        if (!playerList[i]->IsDead()) {
            return false;
        }
    }
    return true;
}

void Simulator::APP_Event_TimeUp() {
    for (int i = 0; i < playerList.size(); ++i) {
        InternalEvent_KillPlayer(playerList[i], sim_globals::ENEMYTYPE_TIME, 0, 0, 0, 0);
    }
}

void Simulator::APP_Event_Suicide(int pID) {
    InternalEvent_KillPlayer(playerList[pID], sim_globals::ENEMYTYPE_SUICIDE, 0, 0, 0, 0);
}

bool Simulator::APP_IsPlayerDead(int pID) {
    return playerList[pID]->IsDead();
}

bool Simulator::APP_IsGameDone() {
    return STATEFLAG_won || AreAllPlayersDead();
}

bool Simulator::APP_DidPlayerWin() {
    if (!APP_IsGameDone()) {
        return false;
    }
    if (STATEFLAG_won) {
        return true;
    }
    return false;
}

void Simulator::APP_EnablePlayer(int pID) {
    playerList[pID]->APP_Enable();
}

void Simulator::APP_DisablePlayer(int pID) {
    playerList[pID]->APP_Disable();
}

void Simulator::App_EnableAllPlayers() {
    for (int i = 0; i < playerList.size(); ++i) {
        playerList[i]->APP_Enable();
    }
}

void Simulator::App_DisableAllPlayers() {
    for (int i = 0; i < playerList.size(); ++i) {
        playerList[i]->APP_Disable();
    }
}

int Simulator::APP_GetNumGoldCollectedDuringTick(int pID) {
    return num_gold_collected_during_tick[pID];
}

bool Simulator::APP_IsPlaybackFinished() {
    for (int i = 0; i < playerList.size(); ++i) {
        if (!playerList[i]->inputsource->IsReplayFinished()) {
            return false;
        }
    }
    return true;
}

void Simulator::APP_GetReplayData(vector<string>& outReplayData) {
    for (int i = 0; i < playerList.size(); ++i) {
        string replayData = playerList[i]->inputsource->DumpString();
        outReplayData.push_back(replayData);
    }
}

vector<vector<ByteArray>> Simulator::APP_GetReplayBytes() {
    vector<vector<ByteArray>> replayBytes;
    for (int i = 0; i < playerList.size(); ++i) {
        vector<ByteArray> replayData = playerList[i]->inputsource->DumpFrames();
        replayBytes.push_back(replayData);
    }
    return replayBytes;
}

void Simulator::DEBUG_SetPlayerPosVel(const vec2& pos, const vec2& vel) {
    for (int i = 0; i < playerList.size(); ++i) {
        playerList[i]->DEBUG_SetPosVel(pos, vel);
    }
}

void Simulator::DEATHMATCH_RespawnPlayer(int pID) {
    if (playerList[pID]->IsDead()) {
        playerList[pID]->DEBUG_Respawn(playerList[pID]->GetPos());
    }
}

void Simulator::DEATHMATCH_GibPlayer(int pID, double deathPosX, double deathPosY, double deathForceX, double deathForceY) {
    if (!playerList[pID]->IsDead()) {
        playerList[pID]->SIM_Kill(sim_globals::ENEMYTYPE_MINE, 0, 0, 0, 0);
    }
}

void Simulator::DEBUG_ToggleRagdoll(const vec2& mousePos) {
    for (int i = 0; i < playerList.size(); ++i) {
        if (playerList[i]->IsDead()) {
            playerList[i]->DEBUG_Respawn(mousePos);
        } else {
            vec2 playerPos = playerList[i]->GetPos();
            double playerRadius = playerList[i]->GetRadius();
            vec2 deathDirection = mousePos.To(playerPos);
            double deathForceMag = min(10.0, deathDirection.Len());
            deathDirection.Normalize();
            vec2 deathForce = deathDirection.Clone();
            deathForce.Scale(deathForceMag);
            playerList[i]->SIM_Kill(sim_globals::ENEMYTYPE_DEBUG, playerPos.x - deathDirection.x * playerRadius, playerPos.y - deathDirection.y * playerRadius, deathForce.x, deathForce.y);
        }
    }
}

void Simulator::DEBUG_ToggleExploded() {
    for (int i = 0; i < playerList.size(); ++i) {
        if (playerList[i]->IsDead()) {
            if (playerList[i]->DEBUG_GetRagdoll().DEBUG_IsExploded()) {
                playerList[i]->DEBUG_GetRagdoll().UnexplodeRagdoll();
            } else {
                playerList[i]->DEBUG_GetRagdoll().ExplodeRagdoll(this);
            }
        }
    }
}

void Simulator::DEBUG_GrabRagdoll(const vec2& pos, const vec2& vel) {
    for (int i = 0; i < playerList.size(); ++i) {
        if (playerList[i]->IsDead()) {
            playerList[i]->DEBUG_GetRagdoll().TESTING_SetPosVel(pos, vel);
        }
    }
}

void Simulator::DEBUG_Draw_Tiles(SimpleRenderer& rend) {
    //rend.SetStyle(0, 0, 100);
    //rend.DrawAABB(0, GRID_NUM_COLS * GRID_CELL_SIZE, 0, GRID_NUM_ROWS * GRID_CELL_SIZE);
    //rend.SetStyle(0, 0xAAAAAA, 100);

    for (int u = 0; u < GRID_NUM_COLS; ++u) {
        for (int v = 0; v < GRID_NUM_ROWS; ++v) {
            vector<Segment*> segments = segGrid.DEBUG_GetCellContentsFromGridspacePosition(u, v);
            for (int i = 0; i < segments.size(); ++i) {
                segments[i]->DebugDraw_Simple(rend);
            }
        }
    }
}

void Simulator::DEBUG_Draw_Edges(SimpleRenderer& rend) {
    edgeGrid.Debug_Draw(rend);
}

void Simulator::DEBUG_Draw_objGrid(SimpleRenderer& rend) {
    objGrid.Debug_Draw(rend);
}

void Simulator::DEBUG_Draw_Grid(SimpleRenderer& rend) {
    //rend.SetStyle(0, 0xAAAAAA, 10);
    for (int u = 0; u < GRID_NUM_COLS; ++u) {
        for (int v = 0; v < GRID_NUM_ROWS; ++v) {
            //rend.DrawAABB(u * GRID_CELL_SIZE, (u + 1) * GRID_CELL_SIZE, v * GRID_CELL_SIZE, (v + 1) * GRID_CELL_SIZE);
        }
    }
}

void Simulator::DEBUG_Draw_Entities(SimpleRenderer& rend) {
    for (int i = 0; i < objList.size(); ++i) {
        //rend.SetStyle(0, 0, 100);
        objList[i]->Debug_Draw(rend);
    }
    for (int i = 0; i < playerList.size(); ++i) {
        playerList[i]->Draw(rend);
    }
}
