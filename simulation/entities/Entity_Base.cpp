#pragma once

#include "..\\..\\math\\vec2.cpp"
#include "..\\Simulator.cpp"
#include "..\\ninja\\Ninja.cpp"

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
        virtual bool CollideVsCircle_Logical(Simulator& param1, Ninja& param2, collision_result_logical& param3, const vec2& param4, const vec2& param5, const vec2& param6, double param7, double param8);
        virtual void Think(Simulator& param1);
        virtual void Move(Simulator& param1);
        virtual EntityGraphics* GenerateGraphicComponent();
        virtual void Debug_Draw(SimpleRenderer& param1);
};

Entity_Base::Entity_Base() : UID(-1), grid_index(-1) {}

void Entity_Base::GAME_SetUID(unsigned int uid) {
    UID = static_cast<int>(uid);
}

unsigned int Entity_Base::GetUID() const {
    return static_cast<unsigned int>(UID);
}

int Entity_Base::GRID_GetGridIndex() const {
    return grid_index;
}

void Entity_Base::GRID_SetGridIndex(int gridIndex) {
    grid_index = gridIndex;
}

bool Entity_Base::CollideVsCircle_Physical(collision_result_physical& param1, const vec2& param2, const vec2& param3, const vec2& param4, double param5) {
    return false;
}

bool Entity_Base::CollideVsCircle_Logical(Simulator& param1, Ninja& param2, collision_result_logical& param3, const vec2& param4, const vec2& param5, const vec2& param6, double param7, double param8) {
    return false;
}

void Entity_Base::Think(Simulator& param1) {

}

void Entity_Base::Move(Simulator& param1) {

}

EntityGraphics* Entity_Base::GenerateGraphicComponent() {
    return nullptr;
}

void Entity_Base::Debug_Draw(SimpleRenderer& param1) {

}