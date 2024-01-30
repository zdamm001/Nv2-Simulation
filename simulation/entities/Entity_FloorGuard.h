#pragma once

#include "Entity_Base.h"
//#include "..\\..\\audiovisual\\entitygraphics\\EntityGraphics_FloorGuard.h"
#include "..\\..\\math\\vec2.h"
//#include "simpleFramework\\SimpleRenderer.h"
#include "..\\Simulator.h"
#include "..\\collision\\Grid_Edges.h"
#include "..\\collision\\Grid_Entity.h"
#include "..\\collision\\colutils.h"
#include "..\\ninja\\Ninja.h"
#include "..\\sim_globals.h"
class EntityGraphics_FloorGuard;

class Entity_FloorGuard : public Entity_Base {
    private:
        vec2 pos;
        double speed;
        double r;
        int CUR_STATE;
        double margin;
    public:
        Entity_FloorGuard(Grid_Entity& entities, double x, double y);
        Entity_FloorGuard(Grid_Entity& entities, entitySave& entity);
        bool CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) override;
        void Think(Simulator* sim) override;
        void Move(Simulator* sim) override;
        EntityGraphics* GenerateGraphicComponent() override;
        void GFX_UpdateState(EntityGraphics_FloorGuard* graphic);
        void Debug_Draw(SimpleRenderer& rend) override;
        // ByteArray saveState() override;
        void saveState(entitySave& state) override;
};