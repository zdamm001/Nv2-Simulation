#pragma once

#include "Entity_Base.h"
#include "..\\..\\math\\vec2.h"
//#include "..\\simpleFramework\\SimpleRenderer.h"
#include "..\\Simulator.h"
#include "..\\collision\\Grid_Edges.h"
#include "..\\collision\\Grid_Entity.h"
#include "..\\collision\\colutils.h"
#include "..\\ninja\\Ninja.h"
#include "..\\sim_globals.h"

class EntityGraphics_Thwomp;

class Entity_Thwomp : public Entity_Base {
    private:
        vec2 pos;
        vec2 anchor;
        double r;
        double fallspeed;
        double raisespeed;
        int CUR_STATE;
        int falldir;
        bool isHorizontal;
        vec2 n;
    public:
        Entity_Thwomp(Grid_Entity* entities, double x, double y, int fallDir, bool isHorizontal);
        Entity_Thwomp(Grid_Entity* entities, entitySave& entity);
        bool CollideVsCircle_Physical(collision_result_physical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius) override;
        bool CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) override;
        void Think(Simulator* sim) override;
        void Move(Simulator* sim) override;
        EntityGraphics* GenerateGraphicComponent() override;
        void GFX_UpdateState(EntityGraphics_Thwomp* graphic);
        void Debug_Draw(SimpleRenderer& rend) override;
        // ByteArray saveState() override;
        void saveState(entitySave& state) override;
};