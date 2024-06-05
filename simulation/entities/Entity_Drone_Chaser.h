#pragma once

#include "Entity_Drone_Zap.h"
#include "..\\..\\math\\vec2.h"
//#include "simpleFramework\\SimpleRenderer.h"
#include "..\\Simulator.h"
#include "..\\collision\\Grid_Edges.h"
#include "..\\collision\\Grid_Entity.h"
#include "..\\ninja\\Ninja.h"

class EntityGraphics_Drone_Chaser;

class Entity_Drone_Chaser : public Entity_Drone_Zap {
    private:
        bool isChasing;
        double speed_regular;
        double speed_chasing;
        int old_chase_DIR;
        bool gfx_startedChasing;
    public:
        Entity_Drone_Chaser(Grid_Entity& entities, double x, double y, unsigned int facingDir, unsigned int moveType);
        Entity_Drone_Chaser(Grid_Entity& entities, entitySave& entity);
        void Think(Simulator* sim) override;
    private:
        void StartChasing(unsigned int newChaseDir);
        void StopChasing(unsigned int newFacingDir);
    protected:
        bool ChooseNextDirAndGoal(Grid_Edges& edges, const vector<Ninja*>& playerList) override;
    public:
        EntityGraphics* GenerateGraphicComponent();
        void GFX_UpdateState(EntityGraphics_Drone_Chaser* graphic);
        void Debug_Draw(SimpleRenderer& rend) override;
        void saveState(entitySave& state) override;
};
