#include "Entity_Drone_Chaingun.h"
#include "..\\..\\audiovisual\\entitygraphics\\EntityGraphics_Drone_Chaingun.h"

Entity_Drone_Chaingun::Entity_Drone_Chaingun(Grid_Entity* entities, double x, double y, unsigned int facingDir, unsigned int moveType)
    : Entity_Drone_Shooter_Base(entities, x, y, 12.0 * (1.0 / 14.0) * 0.75 * (40.0 / sim_globals::sim_rate), facingDir, moveType, 35 * (sim_globals::sim_rate / 40), 60 * (sim_globals::sim_rate / 40)) {
    chaingun_rate = 6.0 * (sim_globals::sim_rate / 40);
    chaingun_count = 0;
    chaingun_timer = 0;
    chaingun_HACKY_hitmode = 0;
}

Entity_Drone_Chaingun::Entity_Drone_Chaingun(Grid_Entity* entities, entitySave& entity)
    : Entity_Drone_Shooter_Base(entities, entity, 12.0 * (1.0 / 14.0) * 0.75 * (40.0 / sim_globals::sim_rate), 35 * (sim_globals::sim_rate / 40), 60 * (sim_globals::sim_rate / 40)) {
    chaingun_rate = 6.0 * (sim_globals::sim_rate / 40);
    chaingun_count = entity.extra;
    chaingun_timer = entity.timer2;
    chaingun_dir = entity.dir;
    chaingun_sweep = entity.vel;
    if (GetFiringState() == FIRING_STATE_FIRING) chaingun_HACKY_hitmode = 1;
    else chaingun_HACKY_hitmode = 0;
}

void Entity_Drone_Chaingun::Start_Prefiring(Simulator* sim, const vec2& ninjaPos) {

}

void Entity_Drone_Chaingun::Update_Prefiring(Simulator* sim, const vec2& ninjaPos) {
    double dx = ninjaPos.x - pos.x;
    double dy = ninjaPos.y - pos.y;
    double angleDiff = mathutils::WrapAngle_Shortest(atan2(dy, dx) - gfxorn);
    gfxorn += 0.2 * angleDiff;
}

void Entity_Drone_Chaingun::Start_Firing(Simulator* sim, const vec2& ninjaPos, const vec2& ninjaVel) {
    chaingun_count = 0;
    chaingun_timer = 0;
    chaingun_HACKY_hitmode = 0;
    
    double dx = ninjaPos.x - pos.x;
    double dy = ninjaPos.y - pos.y;
    double dist = sqrt(dx * dx + dy * dy);
    
    if (dist == 0) {
        chaingun_dir.x = 1;
        chaingun_dir.y = 0;
        chaingun_sweep.x = 0;
        chaingun_sweep.y = 0;
    } else {
        chaingun_dir.x = dx / dist;
        chaingun_dir.y = dy / dist;
        double crossProductloc = -chaingun_dir.y * ninjaVel.x + chaingun_dir.x * ninjaVel.y;
        
        if (crossProductloc < 0) {
            chaingun_sweep.x = chaingun_dir.y;
            chaingun_sweep.y = -chaingun_dir.x;
        } else {
            chaingun_sweep.x = -chaingun_dir.y;
            chaingun_sweep.y = chaingun_dir.x;
        }
    }
}

bool Entity_Drone_Chaingun::Update_Firing(Simulator* sim) {//fix var names
    ++chaingun_timer;

    if (chaingun_rate <= chaingun_timer) {
        chaingun_timer = 0;

        if (chaingun_maxbullets < chaingun_count) {
            return true;
        }

        ++chaingun_count;

        double spreadFactor = (static_cast<double>(chaingun_count) / chaingun_maxbullets - 0.5) * chaingun_spread;

        double newDirX = chaingun_dir.x + spreadFactor * chaingun_sweep.x;
        double newDirY = chaingun_dir.y + spreadFactor * chaingun_sweep.y;

        double dirLength = sqrt(newDirX * newDirX + newDirY * newDirY);

        newDirX /= dirLength;
        newDirY /= dirLength;

        gfxorn = atan2(newDirY, newDirX);

        double hitDist = sim->segGrid->GetRaycastDistance(pos.x, pos.y, newDirX, newDirY, chaingun_hit_pos, chaingun_hit_n);

        //sim->HACKY_GetParticleManager().Spawn_ChainBullet(pos, chaingun_hit_pos);

        for (int i = 0; i < sim->playerList.size(); ++i) {
            if (!sim->playerList[i]->IsDead()) {
                if (colutils::Overlap_Circle_Vs_Segment(sim->playerList[i]->GetPos(), sim->playerList[i]->GetRadius(), pos, chaingun_hit_pos, hitDist)) {
                    double deltaX = sim->playerList[i]->GetPos().x - pos.x;
                    double deltaY = sim->playerList[i]->GetPos().y - pos.y;
                    double dotProduct = newDirX * deltaX + newDirY * deltaY;
                    double projX = pos.x + dotProduct * newDirX;
                    double projY = pos.y + dotProduct * newDirY;
                    chaingun_hit_pos.x = projX;
                    chaingun_hit_pos.y = projY;
                    sim->Event_PlayerWasKilled(sim->playerList[i], sim_globals::ENEMYTYPE_CHAINGUN, projX, projY, newDirX * 5, newDirY * 5);
                }
            }
        }

        chaingun_HACKY_hitmode = 1;
    }

    return false;
}

void Entity_Drone_Chaingun::Start_Postfiring(Simulator* sim) {
    if (chaingun_HACKY_hitmode < 2) {
        chaingun_HACKY_hitmode = 0;
    }
}

EntityGraphics* Entity_Drone_Chaingun::GenerateGraphicComponent() {
    return new EntityGraphics_Drone_Chaingun(this);
}

void Entity_Drone_Chaingun::GFX_UpdateState(EntityGraphics_Drone_Chaingun* graphic) {
    graphic->pos.x = pos.x;
    graphic->pos.y = pos.y;
    graphic->orn = gfxorn;
    int firingState = GetFiringState();
    if (firingState == FIRING_STATE_IDLE) {
        graphic->anim = EntityGraphics_Drone_Chaingun::ANIM_MOVE;
    } else if (firingState == FIRING_STATE_PREFIRING) {
        graphic->anim = EntityGraphics_Drone_Chaingun::ANIM_PREFIRE;
    } else if (firingState == FIRING_STATE_POSTFIRING) {
        graphic->anim = EntityGraphics_Drone_Chaingun::ANIM_POSTFIRE;
    } else if (firingState == FIRING_STATE_FIRING) {
        graphic->anim = EntityGraphics_Drone_Chaingun::ANIM_FIRING;
    }
}

void Entity_Drone_Chaingun::Debug_Draw(SimpleRenderer& rend) {
    Entity_Drone_Shooter_Base::Debug_Draw(rend);
    //rend.SetStyle(4, 0x888888, 50);
    //rend.DrawCircle(pos.x, pos.y, r / 2);
    if (chaingun_HACKY_hitmode == 1) {
        //rend.SetStyle(0, 0x888888, 100 * (1 - static_cast<double>(chaingun_timer) / static_cast<double>(chaingun_rate)));
        //rend.DrawLine(pos.x, pos.y, chaingun_hit_pos.x, chaingun_hit_pos.y);
        //rend.DrawLine(chaingun_hit_pos.x, chaingun_hit_pos.y, chaingun_hit_pos.x + 4 * chaingun_hit_n.x, chaingun_hit_pos.y + 4 * chaingun_hit_n.y);
    }
}

void Entity_Drone_Chaingun::saveState(entitySave& state) {
    Entity_Drone_Shooter_Base::saveState(state);
    state.etype = edat::ETYPE_CHAINGUN;
    state.extra = chaingun_count;
    state.timer2 = chaingun_timer;
    state.dir = chaingun_dir;
    state.vel = chaingun_sweep;
}