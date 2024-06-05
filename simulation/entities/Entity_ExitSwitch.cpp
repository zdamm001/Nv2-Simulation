#include "Entity_ExitSwitch.h"
#include "..\\..\\audiovisual\\entitygraphics\\EntityGraphics_ExitSwitch.h"

Entity_ExitSwitch::Entity_ExitSwitch(Grid_Entity* entities, double x, double y, Entity_ExitDoor* door)
    : pos(x, y), r(12 * 0.5), door(door) {
    entities->ENTITY_Add(pos, this);
}

Entity_ExitSwitch::Entity_ExitSwitch(Grid_Entity* entities, entitySave& entity, Entity_ExitDoor* door)
    : pos(entity.pos), r(12 * 0.5), door(door) {
    entities->ENTITY_Add(pos, this);
}

bool Entity_ExitSwitch::CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) {
    if (ninja != nullptr) {
        if (colutils::Overlap_Circle_Vs_Circle(pos, r, circlePosition, circleRadius)) {
            door->SWITCH_OpenTheExit(sim->objGrid);
            sim->objGrid->ENTITY_Remove(this);
        }
    }
    return false;
}

EntityGraphics* Entity_ExitSwitch::GenerateGraphicComponent() {
    return new EntityGraphics_ExitSwitch(this, pos.x, pos.y);
}

void Entity_ExitSwitch::GFX_UpdateState(EntityGraphics_ExitSwitch* graphic) {
    if (door->SWITCH_IsOpen()) {
        graphic->anim = EntityGraphics_ExitSwitch::ANIM_OPEN;
    } else {
        graphic->anim = EntityGraphics_ExitSwitch::ANIM_CLOSED;
    }
}

void Entity_ExitSwitch::Debug_Draw(SimpleRenderer& rend) {
    if (door->SWITCH_IsOpen()) {
        //rend.SetStyle(0, 0, 10);
    } else {
        //rend.SetStyle(0, 0, 100);
    }
    //rend.DrawSquare(pos.x, pos.y, r);
    //rend.DrawCross(pos.x, pos.y, r);
}

// ByteArray Entity_ExitSwitch::saveState() {
//     ByteArray state;
//     state.writeByte(edat::STRUCTTYPE_);
//     state.writeDouble(pos.x);
//     state.writeDouble(pos.y);
//     state.writeBoolean();
//     return state;
// }

void Entity_ExitSwitch::saveState(entitySave& state) {
    Entity_Base::saveState(state);
    state.etype = edat::ETYPE_EXIT_SWITCH;
    state.pos = pos;
    state.extra = door->GetUID();
}