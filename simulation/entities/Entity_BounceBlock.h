#pragma once

class EntityGraphics {};
class EntityGraphics_BounceBlock : public EntityGraphics {};
#include "..\\..\\math\\vec2.h"
class SimpleRenderer {};
#include "..\\Simulator.h"
#include "..\\collision\\Grid_Entity.h"
#include "..\\collision\\colutils.h"
#include "..\\ninja\\Ninja.h"
#include "..\\sim_globals.h"

class Entity_BounceBlock : public Entity_Base {
    private:
        vec2 pos;
        vec2 vel;
        vec2 anchor;
        double r;
        double stiff;
        double damp;
        double mass;
        bool isSleeping;
        vec2 n;
    public:
        Entity_BounceBlock(Grid_Entity& gridEntity, double x, double y);
        bool CollideVsCircle_Physical(collision_result_physical& result, const vec2& circleCenter, const vec2& circleVelocity, const vec2& squareCenter, double circleRadius) override;
        bool CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) override;
        void Think(Simulator* sim) override;
        void Move(Simulator* sim) override;
        EntityGraphics* GenerateGraphicComponent() override;
        void GFX_UpdateState(EntityGraphics_BounceBlock* graphic);
        void Debug_Draw(SimpleRenderer& rend) override;
};
