#pragma once

#include "Entity_Base.h"
#include "..\\..\\math\\vec2.h"
#include "..\\Simulator.h"
#include "..\\collision\\colutils.h"
#include "..\\ninja\\Ninja.h"

class EntityGraphics_OnewayPlatform;

class Entity_OnewayPlatform : public Entity_Base {
    private:
        vec2 pos;
        vec2 n;
        double r;
    public:
        Entity_OnewayPlatform(Grid_Entity& entities, double x, double y, double nx, double ny);
        Entity_OnewayPlatform(Grid_Entity& entities, entitySave& entity);
        bool CollideVsCircle_Physical(collision_result_physical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius) override;
        bool CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) override;
    private:
        double CalculatePenetration(const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon);
    public:
        EntityGraphics* GenerateGraphicComponent() override;
        void Debug_Draw(SimpleRenderer& rend) override;
        // ByteArray saveState() override;
        void saveState(entitySave& state) override;
};
