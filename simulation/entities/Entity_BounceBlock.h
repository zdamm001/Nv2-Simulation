#pragma once

#include "..\\..\\math\\vec2.h"
#include "..\\Simulator.h"
#include "..\\collision\\Grid_Entity.h"
#include "..\\collision\\colutils.h"
#include "..\\ninja\\Ninja.h"
#include "..\\sim_globals.h"

class SimpleRenderer;

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
        bool CollideVsCircle_Physical(collision_result_physical& collisionResult, const vec2& circleCenter, const vec2& circleVelocity, const vec2& squareCenter, double circleRadius) override;
};
