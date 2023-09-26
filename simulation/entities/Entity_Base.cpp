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

bool Entity_Base::CollideVsCircle_Physical(collision_result_physical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius) {
    return false;
}

bool Entity_Base::CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) {
    return false;
}

void Entity_Base::Think(Simulator* sim) {

}

void Entity_Base::Move(Simulator* sim) {

}

EntityGraphics* Entity_Base::GenerateGraphicComponent() {
    return nullptr;
}

void Entity_Base::Debug_Draw(SimpleRenderer& rend) {

}