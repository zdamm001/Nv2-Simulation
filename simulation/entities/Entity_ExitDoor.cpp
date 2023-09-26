#include "Entity_ExitDoor.h"

Entity_ExitDoor::Entity_ExitDoor(double x, double y)
    : pos(x, y), r(12), isOpen(false) {
}

bool Entity_ExitDoor::CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) {
    if (ninja != nullptr) {
        if (colutils::Overlap_Circle_Vs_Circle(pos, r, circlePosition, circleRadius)) {
            sim->Event_Exit_HitPlayer(ninja);
        }
    }
    return false;
}

void Entity_ExitDoor::SWITCH_OpenTheExit(Grid_Entity& entities) {
    isOpen = true;
    entities.ENTITY_Add(pos, this);
}

bool Entity_ExitDoor::SWITCH_IsOpen() {
    return isOpen;
}

EntityGraphics* Entity_ExitDoor::GenerateGraphicComponent() {
    //return new EntityGraphics_ExitDoor(this, pos.x, pos.y);
}

void Entity_ExitDoor::GFX_UpdateState(EntityGraphics_ExitDoor* graphic) {
    if (isOpen) {
        //graphic->anim = EntityGraphics_ExitDoor::ANIM_OPEN;
    } else {
        //graphic->anim = EntityGraphics_ExitDoor::ANIM_CLOSED;
    }
}

void Entity_ExitDoor::Debug_Draw(SimpleRenderer& rend) {
    if (isOpen) {
        //rend.SetStyle(0, 0, 100);
        //rend.DrawSquare(pos.x, pos.y, r);
        //rend.DrawSquare(pos.x, pos.y, r - 2);
    } else {
        //rend.SetStyle(0, 0, 30);
        //rend.DrawCross(pos.x, pos.y, r);
        //rend.DrawSquare(pos.x, pos.y, r);
    }
}
