#include "Entity_Gold.h"

Entity_Gold::Entity_Gold(Grid_Entity& entities, double x, double y)
    : pos(x, y), r(12 * 0.5), isCollected(false) {
    entities.ENTITY_Add(pos, this);
}

Entity_Gold::Entity_Gold(Grid_Entity& entities, entitySave& entity)
    : pos(entity.pos), r(6), isCollected(entity.is) {
    if (!isCollected) entities.ENTITY_Add(pos, this);
}

bool Entity_Gold::CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) {
    if (ninja != nullptr) {
        if (colutils::Overlap_Circle_Vs_Circle(pos, r, circlePosition, circleRadius)) {
            if (sim->Event_Gold_HitPlayer(ninja)) {
                isCollected = true;
                sim->objGrid.ENTITY_Remove(this);
                //sim->HACKY_GetSoundManager().PlaySound_Gold();
            }
        }
    }
    return false;
}

EntityGraphics* Entity_Gold::GenerateGraphicComponent() {
    return nullptr;
    //return new EntityGraphics_Gold(this, pos.x, pos.y);
}

void Entity_Gold::GFX_UpdateState(EntityGraphics_Gold* graphic) {
    if (isCollected) {
        //graphic->anim = EntityGraphics_Gold::ANIM_COLLECTED;
    } else {
        //graphic->anim = EntityGraphics_Gold::ANIM_NOT_COLLECTED;
    }
}

void Entity_Gold::Debug_Draw(SimpleRenderer& rend) {
    if (isCollected) {
        //rend.SetStyle(0, 0, 10);
    } else {
        //rend.SetStyle(0, 0, 100);
    }
    //rend.DrawSquare(pos.x, pos.y, r / 2);
    //rend.DrawCircle(pos.x, pos.y, r);
}

// ByteArray Entity_Gold::saveState() {
//     ByteArray state;
//     state.writeByte(edat::STRUCTTYPE_GOLD);
//     state.writeDouble(pos.x);
//     state.writeDouble(pos.y);
//     state.writeBoolean(isCollected);
//     return state;
// }

void Entity_Gold::saveState(entitySave& state) {
    Entity_Base::saveState(state);
    state.etype = edat::ETYPE_GOLD;
    state.pos = pos;
    state.is = isCollected;
}