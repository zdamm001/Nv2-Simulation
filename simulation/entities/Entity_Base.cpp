#include "Entity_Base.h"

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

bool Entity_Base::CollideVsCircle_Logical(Simulator* param1, Ninja& param2, collision_result_logical& param3, const vec2& param4, const vec2& param5, const vec2& param6, double param7, double param8) {
    return false;
}

void Entity_Base::Think(Simulator* param1) {

}

void Entity_Base::Move(Simulator*aram1) {

}

EntityGraphics* Entity_Base::GenerateGraphicComponent() {
    return nullptr;
}

void Entity_Base::Debug_Draw(SimpleRenderer& param1) {

}