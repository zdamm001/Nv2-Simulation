#include "Entity_Drone_Zap.h"
#include "..\\..\\audiovisual\\entitygraphics\\EntityGraphics_Drone_Zap.h"

Entity_Drone_Zap::Entity_Drone_Zap(Grid_Entity& entities, double x, double y, unsigned int facingDir, unsigned int moveType)
    : Entity_Drone_Base(entities, x, y, 12.0 * (1.0 / 14.0) * 2 * (40 / sim_globals::sim_rate), facingDir, moveType) {}

Entity_Drone_Zap::Entity_Drone_Zap(Grid_Entity& entities, entitySave& entity)
    : Entity_Drone_Base(entities, entity, 12.0 * (1.0 / 14.0) * 2 * (40 / sim_globals::sim_rate)) {}

bool Entity_Drone_Zap::CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) {
    if (colutils::Overlap_Circle_Vs_Circle(pos, r, circlePosition, circleRadius)) {
        double deltaX = circlePosition.x - pos.x;
        double deltaY = circlePosition.y - pos.y;
        double distance = sqrt(deltaX * deltaX + deltaY * deltaY);
        deltaX /= distance;
        deltaY /= distance;
        //sim->HACKY_GetParticleManager().Spawn_Zap(pos.x + deltaX * r, pos.y + deltaY * r, atan2(deltaY, deltaX) / M_PI * 180);
        if (ninja == nullptr) {
            result.vec_x = deltaX * 12;
            result.vec_y = deltaY * 12 - 4;
            return true;
        }
        sim->Event_PlayerWasKilled(ninja, sim_globals::ENEMYTYPE_ZAP, circlePosition.x - deltaX * circleRadius, circlePosition.y - deltaY * circleRadius, deltaX * 12, deltaY * 12 - 4);
    }
    return false;
}

EntityGraphics* Entity_Drone_Zap::GenerateGraphicComponent() {
    return new EntityGraphics_Drone_Zap(this);
}

void Entity_Drone_Zap::GFX_UpdateState(EntityGraphics_Drone_Zap* graphic) {
    if (graphic) {
        graphic->pos.x = pos.x;
        graphic->pos.y = pos.y;
        graphic->orn = gfxorn;
    }
}

void Entity_Drone_Zap::Debug_Draw(SimpleRenderer& rend) {
    Entity_Drone_Base::Debug_Draw(rend);
    //rend->SetStyle(4, 0x8888FF, 50);
    //rend->DrawCircle(pos.x, pos.y, r / 2);
}

void Entity_Drone_Zap::saveState(entitySave& state) {
    Entity_Drone_Base::saveState(state);
    state.etype = edat::ETYPE_ZAP;
}