#include "Entity_Drone_Laser.h"
#include "..\\..\\audiovisual\\entitygraphics\\EntityGraphics_Drone_Laser.h"

Entity_Drone_Laser::Entity_Drone_Laser(Grid_Entity& entities, double x, double y, unsigned int facingDir, unsigned int moveType)
    : laser_duration(80),  Entity_Drone_Shooter_Base(entities, x, y, 12.0 * (1.0 / 14.0) * 0.5 * (40.0 / sim_globals::sim_rate), facingDir, moveType, 30 * (sim_globals::sim_rate / 40), 40 * (sim_globals::sim_rate / 40)) {
    laser_timer = 0;
    laser_dir = vec2(0, 0);
}

Entity_Drone_Laser::Entity_Drone_Laser(Grid_Entity& entities, entitySave& entity)
    : laser_duration(80),  Entity_Drone_Shooter_Base(entities, entity, 12.0 * (1.0 / 14.0) * 0.5 * (40.0 / sim_globals::sim_rate), 30 * (sim_globals::sim_rate / 40), 40 * (sim_globals::sim_rate / 40)) {
    laser_timer = entity.timer2;
    laser_dir = entity.dir;
    laser_hit_pos = entity.vel;
    laser_hit_n = entity.n;
}

void Entity_Drone_Laser::Start_Prefiring(Simulator* sim, const vec2& ninjaPos) {
    laser_dir.x = ninjaPos.x - pos.x;
    laser_dir.y = ninjaPos.y - pos.y;
    laser_dir.Normalize();
    double hitDist = sim->segGrid.GetRaycastDistance(pos.x, pos.y, laser_dir.x, laser_dir.y, laser_hit_pos, laser_hit_n);
}

void Entity_Drone_Laser::Update_Prefiring(Simulator* sim, const vec2& ninjaPos) {
    double hitDist = sim->segGrid.GetRaycastDistance(pos.x, pos.y, laser_dir.x, laser_dir.y, laser_hit_pos, laser_hit_n);
    //sim->HACKY_GetParticleManager().Spawn_LaserCharge(pos);
}

void Entity_Drone_Laser::Start_Firing(Simulator* sim, const vec2& ninjaPos, const vec2& ninjaVel) {
    laser_timer = 0;
}

bool Entity_Drone_Laser::Update_Firing(Simulator* sim) {    
    double hitDist = sim->segGrid.GetRaycastDistance(pos.x, pos.y, laser_dir.x, laser_dir.y, laser_hit_pos, laser_hit_n);
    //sim->HACKY_GetParticleManager().Spawn_LaserCharge(pos);
    
    for (int i = 0; i < sim->playerList.size(); ++i) {
        if (!sim->playerList[i]->IsDead()) {
            if (colutils::Overlap_Circle_Vs_Segment(sim->playerList[i]->GetPos(), sim->playerList[i]->GetRadius(), pos, laser_hit_pos, hitDist)) {
                double deltaX = sim->playerList[i]->GetPos().x - pos.x;
                double deltaY = sim->playerList[i]->GetPos().y - pos.y;
                double _loc6_ = laser_dir.x * deltaX + laser_dir.y * deltaY;
                double _loc7_ = pos.x + _loc6_ * laser_dir.x;
                double _loc8_ = pos.y + _loc6_ * laser_dir.y;
                sim->Event_PlayerWasKilled(sim->playerList[i], sim_globals::ENEMYTYPE_LASER, _loc7_, _loc8_, laser_dir.x * 6, laser_dir.y * 6);
            }
        }
    }
    
    ++laser_timer;
    
    if (laser_duration <= laser_timer) {
        return true;
    }
    
    return false;
}

void Entity_Drone_Laser::Start_Postfiring(Simulator* sim) {

}

EntityGraphics* Entity_Drone_Laser::GenerateGraphicComponent() {
    return new EntityGraphics_Drone_Laser(this);
}

void Entity_Drone_Laser::GFX_UpdateState(EntityGraphics_Drone_Laser* graphics) {
    if (graphics) {
        graphics->pos.x = pos.x;
        graphics->pos.y = pos.y;
        graphics->orn = gfxorn;
        int firingState = GetFiringState();
        if (firingState == FIRING_STATE_IDLE) {
            graphics->anim = EntityGraphics_Drone_Laser::ANIM_MOVE;
        } else if (firingState == FIRING_STATE_PREFIRING) {
            graphics->anim = EntityGraphics_Drone_Laser::ANIM_PREFIRE;
            graphics->blast_pos.x = laser_hit_pos.x;
            graphics->blast_pos.y = laser_hit_pos.y;
        } else if (firingState == FIRING_STATE_POSTFIRING) {
            graphics->anim = EntityGraphics_Drone_Laser::ANIM_POSTFIRE;
        } else if (firingState == FIRING_STATE_FIRING) {
            graphics->anim = EntityGraphics_Drone_Laser::ANIM_FIRING;
            graphics->blast_scale = 30 + 200 * (laser_timer / laser_duration);
        }
    }
}

void Entity_Drone_Laser::Debug_Draw(SimpleRenderer& rend) {
    Entity_Drone_Shooter_Base::Debug_Draw(rend);
    //rend.SetStyle(4, 0x882222, 50);
    //rend.DrawCircle(pos.x, pos.y, r / 2);
    int firingState = GetFiringState();
    
    if (firingState == FIRING_STATE_PREFIRING) {
        //rend.SetStyle(0, 0x882222, 20);
        //rend.DrawLine(pos.x, pos.y, laser_hit_pos.x, laser_hit_pos.y);
        //rend.DrawLine(laser_hit_pos.x, laser_hit_pos.y, laser_hit_pos.x + laser_hit_n.x * 4, laser_hit_pos.y + laser_hit_n.y * 4);
    } else if (firingState == FIRING_STATE_FIRING) {
        //rend.SetStyle(2, 0x882222, 80);
        //rend.DrawLine(pos.x, pos.y, laser_hit_pos.x, laser_hit_pos.y);
        //rend.DrawLine(laser_hit_pos.x, laser_hit_pos.y, laser_hit_pos.x + laser_hit_n.x * 4, laser_hit_pos.y + laser_hit_n.y * 4);
    }
}

void Entity_Drone_Laser::saveState(entitySave& state) {
    Entity_Drone_Shooter_Base::saveState(state);
    state.etype = edat::ETYPE_LASER;
    state.timer2 = laser_timer;
    state.dir = laser_dir;
    state.vel = laser_hit_pos;
    state.n = laser_hit_n;
}