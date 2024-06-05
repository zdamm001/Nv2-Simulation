#include "Entity_Mine.h"
#include "..\\..\\audiovisual\\entitygraphics\\EntityGraphics_Mine.h"

Entity_Mine::Entity_Mine(Grid_Entity* entities, double x, double y)
    : pos(x, y), r(12.0 * (1.0 / 3.0)), isExploded(false) {
    entities->ENTITY_Add(pos, this);
}

Entity_Mine::Entity_Mine(Grid_Entity* entities, entitySave& entity)
    : pos(entity.pos), r(4), isExploded(entity.is) {
    if (!isExploded) entities->ENTITY_Add(pos, this);
}

bool Entity_Mine::CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) {
    if (colutils::Overlap_Circle_Vs_Circle(pos, r, circlePosition, circleRadius)) {
        //sim->HACKY_GetParticleManager()->Spawn_Explosion(pos);
        isExploded = true;
        sim->objGrid->ENTITY_Remove(this);
        double deltaX = circlePosition.x - pos.x;
        double deltaY = circlePosition.y - pos.y;
        double distance = sqrt(deltaX * deltaX + deltaY * deltaY);
        deltaX /= distance;
        deltaY /= distance;
        if (ninja == nullptr) {
            result.vec_x = deltaX * 16;
            result.vec_y = deltaY * 16;
            return true;
        }
        sim->Event_PlayerWasKilled(ninja, sim_globals::ENEMYTYPE_MINE, circlePosition.x - deltaX * circleRadius, circlePosition.y - deltaY * circleRadius, deltaX * 16, deltaY * 16);
    }
    return false;
}

EntityGraphics* Entity_Mine::GenerateGraphicComponent() {
    return new EntityGraphics_Mine(this, pos.x, pos.y);
}

void Entity_Mine::GFX_UpdateState(EntityGraphics_Mine* graphic) {
    if (isExploded) {
        graphic->anim = EntityGraphics_Mine::ANIM_EXPLODED;
    } else {
        graphic->anim = EntityGraphics_Mine::ANIM_UNEXPLODED;
    }
}

void Entity_Mine::Debug_Draw(SimpleRenderer& rend) {
    if (isExploded) {
        //rend.SetStyle(0, 0, 30);
    } else {
        //rend.SetStyle(0, 0, 100);
    }
    //rend.DrawCross(pos.x, pos.y, r);
    //rend.DrawCircle(pos.x, pos.y, r);
}

// ByteArray Entity_Mine::saveState() {
//     ByteArray state;
//     state.writeByte(edat::STRUCTTYPE_MINE);
//     state.writeDouble(pos.x);
//     state.writeDouble(pos.y);
//     state.writeBoolean(isExploded);
//     return state;
// }

void Entity_Mine::saveState(entitySave& state) {
    Entity_Base::saveState(state);
    state.etype = edat::ETYPE_MINE;
    state.pos = pos;
    state.is = isExploded;
}