#pragma once

#include "..\\..\\math\\vec2.h"
#include "..\\Simulator.h"
#include "..\\ninja\\Ninja.h"

class EntityGraphics;

class Entity_Base {
    private:
        int UID;
        int grid_index;
    public:
        Entity_Base();
        virtual ~Entity_Base() = default;
        void GAME_SetUID(unsigned int param1);
        unsigned int GetUID() const;
        int GRID_GetGridIndex() const;
        void GRID_SetGridIndex(int param1);
        virtual bool CollideVsCircle_Physical(collision_result_physical& param1, const vec2& param2, const vec2& param3, const vec2& param4, double param5);
        virtual bool CollideVsCircle_Logical(Simulator* param1, Ninja& param2, collision_result_logical& param3, const vec2& param4, const vec2& param5, const vec2& param6, double param7, double param8);
        virtual void Think(Simulator* param1);
        virtual void Move(Simulator* param1);
        virtual EntityGraphics* GenerateGraphicComponent();
        virtual void Debug_Draw(SimpleRenderer& param1);
};