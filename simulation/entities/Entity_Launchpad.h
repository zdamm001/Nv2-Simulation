#pragma once

#include "Entity_Base.h"
#include "..\\..\\math\\vec2.h"
//#include "simpleFramework\\SimpleRenderer.h"
#include "..\\Simulator.h"
#include "..\\collision\\Grid_Entity.h"
#include "..\\collision\\colutils.h"
#include "..\\ninja\\Ninja.h"
#include "..\\sim_globals.h"

class EntityGraphics_Launchpad;

class Entity_Launchpad : public Entity_Base {
    private:
        vec2 pos;
        vec2 n;
        double r;
        double strength;
        double pow;
        bool gfx_triggerEvent;
    public:
        Entity_Launchpad(Grid_Entity& entities, double x, double y, double nx, double ny);
        Entity_Launchpad(Grid_Entity& entities, entitySave& entity);
        bool CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) override;
        EntityGraphics* GenerateGraphicComponent() override;
        void GFX_UpdateState(EntityGraphics_Launchpad* graphic);
        void Debug_Draw(SimpleRenderer& rend) override;
        // ByteArray saveState() override;
        void saveState(entitySave& state) override;
};
