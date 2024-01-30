#include "Entity_Launchpad.h"

Entity_Launchpad::Entity_Launchpad(Grid_Entity& entities, double x, double y, double nx, double ny)
    : pos(x, y), n(nx, ny), r(12 * 0.5), strength(12 * (3 / 7)), gfx_triggerEvent(false) {
    entities.ENTITY_Add(pos, this);
}

Entity_Launchpad::Entity_Launchpad(Grid_Entity& entities, entitySave& entity)
    : pos(entity.pos), n(entity.n), r(12 * 0.5), strength(12 * (3 / 7)), gfx_triggerEvent(false) {
    entities.ENTITY_Add(pos, this);
}

bool Entity_Launchpad::CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) {
    if (colutils::Overlap_Circle_Vs_Circle(pos, r, circlePosition, circleRadius)) {
        double deltaX = pos.x - (circlePosition.x - n.x * circleRadius);
        double deltaY = pos.y - (circlePosition.y - n.y * circleRadius);
        epsilon = 0.1;
        if (-epsilon <= n.x * deltaX + n.y * deltaY) {
            double scaleFactor = 1;

            if (n.y < 0) {
                scaleFactor += abs(n.y);
            }

            if (ninja == nullptr) {
                result.vec_x = n.x * 12;
                result.vec_y = n.y * 12;
                gfx_triggerEvent = true;
                return true;
            }

            sim->Event_Launchpad_HitPlayer(ninja, n.x * strength, n.y * strength * scaleFactor);
            gfx_triggerEvent = true;
        }
    }

    return false;
}

EntityGraphics* Entity_Launchpad::GenerateGraphicComponent() {
    return nullptr;
    //return new EntityGraphics_Launchpad(this, pos.x, pos.y, atan2(n.y, n.x));
}

void Entity_Launchpad::GFX_UpdateState(EntityGraphics_Launchpad* graphic) {
    if (gfx_triggerEvent) {
        //graphic->anim = EntityGraphics_Launchpad::ANIM_LAUNCH;
        gfx_triggerEvent = false;
    } else {
        //graphic->anim = EntityGraphics_Launchpad::ANIM_IDLE;
    }
}

void Entity_Launchpad::Debug_Draw(SimpleRenderer& rend) {
    //rend.SetStyle(0, 0, 100);
    //rend.DrawBox(pos.x, pos.y, -n.y * r, n.x * r, n.x * 2, n.y * 2);
    //rend.DrawLine(pos.x, pos.y, pos.x + n.x * 6, pos.y + n.y * 6);
}

// ByteArray Entity_Launchpad::saveState() {
//     ByteArray state;
//     state.writeByte(edat::STRUCTTYPE_LAUNCHPAD);
//     state.writeDouble(pos.x);
//     state.writeDouble(pos.y);
//     state.writeDouble(n.x);
//     state.writeDouble(n.y);
//     return state;
// }

void Entity_Launchpad::saveState(entitySave& state) {
    Entity_Base::saveState(state);
    state.etype = edat::ETYPE_LAUNCHPAD;
    state.pos = pos;
    state.n = n;
}