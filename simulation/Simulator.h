#pragma once
#include <vector>

#include "..\\editor\\edat.h"
#include "..\\flash\\utils\\ByteArray.h"
#include "..\\math\\mathutils.h"
#include "..\\math\\vec2.h"
#include "collision\\Grid_Edges.h"
#include "collision\\Grid_Entity.h"
#include "collision\\Grid_Segment.h"
#include "entities\\Entity_Base.h"
#include "ninja\\Ninja.h"

using namespace std;

class SimpleRenderer;
class GraphicsManager;
class SoundManager;
class ParticleManager;

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
        GraphicsManager* HACKY_gfx;
        SoundManager* HACKY_sfx;
    public:
        Simulator(vector<int> tileIDs, Grid_Segment segGrid, Grid_Edges edgeGrid, Grid_Entity objGrid, vector<Entity_Base*> objList, vector<Ninja*> playerList);
        void HACKY_SetAV(GraphicsManager* gfx, SoundManager* sfx);
        ParticleManager* HACKY_GetParticleManager();
        SoundManager* HACKY_GetSoundManager();
        vector<Entity_Base*> GFX_GetEntityList();
        vector<Ninja*> GFX_GetPlayerList();
        vector<int> GFX_GetTileIDs();
        void Tick(SimpleRenderer* renderer);
    private:
        void InternalEvent_KillPlayer(Ninja* ninja, int enemyType, double deathPosX, double deathPosY, double deathForceX, double deathForceY);
    public:
        void Event_Launchpad_HitPlayer(Ninja* ninja, double launchForceX, double launchForceY);
        void Event_Exit_HitPlayer(Ninja* ninja);
        bool Event_Gold_HitPlayer(Ninja* ninja);
        void Event_PlayerWasKilled(Ninja* ninja, int enemyType, double deathPosX, double deathPosY, double deathForceX, double deathForceY);
    private:
        bool AreAllPlayersDead();
    public:
        void APP_Event_TimeUp();
        void APP_Event_Suicide(int pID);
        bool APP_IsPlayerDead(int pID);
        bool APP_IsGameDone();
        bool APP_DidPlayerWin();
        void APP_EnablePlayer(int pID);
        void APP_DisablePlayer(int pID);
        void App_EnableAllPlayers();
        void App_DisableAllPlayers();
        int APP_GetNumGoldCollectedDuringTick(int pID);
        bool APP_IsPlaybackFinished();
        void APP_GetReplayData(vector<string>& outReplayData);
        vector<vector<ByteArray>> APP_GetReplayBytes();
        void DEBUG_SetPlayerPosVel(const vec2& pos, const vec2& vel);
        void DEATHMATCH_RespawnPlayer(int pID);
        void DEATHMATCH_GibPlayer(int pID, double deathPosX, double deathPosY, double deathForceX, double deathForceY);
        void DEBUG_ToggleRagdoll(const vec2& pos);
        void DEBUG_ToggleExploded();
        void DEBUG_GrabRagdoll(const vec2& pos, const vec2& vel);
        void DEBUG_Draw_Tiles(SimpleRenderer& rend);
        void DEBUG_Draw_Edges(SimpleRenderer& rend);
        void DEBUG_Draw_objGrid(SimpleRenderer& rend);
        void DEBUG_Draw_Grid(SimpleRenderer& rend);
        void DEBUG_Draw_Entities(SimpleRenderer& rend);
};