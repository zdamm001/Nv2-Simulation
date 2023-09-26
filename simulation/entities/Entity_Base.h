#pragma once

#include "..\\..\\math\\vec2.h"
class Simulator;
class Ninja;
class EntityGraphics;
class collision_result_physical;
class collision_result_logical;
class SimpleRenderer;

class Entity_Base {
    private:
        int UID;
        int grid_index;
    public:
        Entity_Base();
        virtual ~Entity_Base() = default;
        virtual void GAME_SetUID(unsigned int uid) final;
        virtual unsigned int GetUID() const final;
        virtual int GRID_GetGridIndex() const final;
        virtual void GRID_SetGridIndex(int gridIndex) final;
        virtual bool CollideVsCircle_Physical(collision_result_physical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius);
        virtual bool CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon);
        virtual void Think(Simulator* sim);
        virtual void Move(Simulator* sim);
        virtual EntityGraphics* GenerateGraphicComponent();
        virtual void Debug_Draw(SimpleRenderer& rend);
};