#include "Entity_Rocket.h"
#include "..\\..\\audiovisual\\entitygraphics\\EntityGraphics_Rocket.h"

Entity_Rocket::Entity_Rocket(Grid_Entity* entities, double x, double y) {
    accel_start = 0.1 * (40.0 / sim_globals::sim_rate) * (40.0 / sim_globals::sim_rate);
    maxspeed = 12.0 * (2.0 / 7.0) * (40.0 / sim_globals::sim_rate);
    accel_rate = pow(1.1, 40.0 / sim_globals::sim_rate);
    turn_rate = 0.1 * (40.0 / sim_globals::sim_rate);
    prefire_delay = 10 * (sim_globals::sim_rate / 40.0);
    prediction_scale = sim_globals::sim_rate / 40.0;
    pos = vec2(x, y);
    rocket_pos = vec2(x, y);
    rocket_dir = vec2(1, 0);
    rocket_speed = 0.0;
    rocket_accel = accel_start;
    shot_timer = 0.0;
    CUR_STATE = STATE_IDLE;
    targetIndex = -1;
    gfx_PREV_STATE = CUR_STATE;
}

Entity_Rocket::Entity_Rocket(Grid_Entity* entities, entitySave& entity) {
    accel_start = 0.1 * (40.0 / sim_globals::sim_rate) * (40.0 / sim_globals::sim_rate);
    maxspeed = 12.0 * (2.0 / 7.0) * (40.0 / sim_globals::sim_rate);
    accel_rate = pow(1.1, 40.0 / sim_globals::sim_rate);
    turn_rate = 0.1 * (40.0 / sim_globals::sim_rate);
    prefire_delay = 10 * (sim_globals::sim_rate / 40.0);
    prediction_scale = sim_globals::sim_rate / 40.0;
    pos = entity.pos;
    rocket_pos = entity.pos2;
    rocket_dir = entity.dir;
    rocket_speed = entity.vel.x;
    rocket_accel = entity.vel.y;
    shot_timer = entity.timer3;
    CUR_STATE = entity.state;
    targetIndex = entity.index;
    gfx_PREV_STATE = entity.extra;
}

bool Entity_Rocket::CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) {
    if (CUR_STATE != STATE_HOMING) {
        return false;
    }
    
    if (colutils::Overlap_Circle_Vs_Circle(rocket_pos, 0, circlePosition, circleRadius)) {
        Event_Explode(sim);
        double deltaX = circlePosition.x - rocket_pos.x;
        double deltaY = circlePosition.y - rocket_pos.y;
        
        if (ninja == nullptr) {
            result.vec_x = deltaX * 4.0;
            result.vec_y = deltaY * 4.0;
            return true;
        }
        
        sim->Event_PlayerWasKilled(ninja, sim_globals::ENEMYTYPE_ROCKET, rocket_pos.x, rocket_pos.y, deltaX, deltaY);
    }
    
    return false;
}

void Entity_Rocket::Think(Simulator* sim) {
    gfx_PREV_STATE = CUR_STATE;

    if (CUR_STATE == STATE_IDLE) {
        int ninjaID = entity_helpers::TryToAquireTarget(pos, sim->playerList, sim->segGrid);
        if (ninjaID >= 0) {
            shot_timer = 0;
            CUR_STATE = STATE_PREFIRE;
            targetIndex = ninjaID;
        }
    }
    else if (CUR_STATE == STATE_PREFIRE) {
        if (sim->playerList[targetIndex]->IsDead()) {
            CUR_STATE = STATE_IDLE;
        }
        else {
            ++shot_timer;
            if (prefire_delay <= shot_timer) {
                rocket_pos = pos;
                rocket_accel = accel_start;
                rocket_speed = 0;

                double deltaX = sim->playerList[targetIndex]->GetPos().x - pos.x;
                double deltaY = sim->playerList[targetIndex]->GetPos().y - pos.y;
                double distanceSquared = deltaX * deltaX + deltaY * deltaY;

                if (distanceSquared != 0) {
                    deltaX /= sqrt(distanceSquared);
                    deltaY /= sqrt(distanceSquared);
                    rocket_dir.x = deltaX;
                    rocket_dir.y = deltaY;
                } else {
                    rocket_dir.x = 1;
                    rocket_dir.y = 0;
                }

                sim->objGrid->ENTITY_Add(rocket_pos, this);
                CUR_STATE = STATE_HOMING;
            }
        }
    }
    else if (CUR_STATE == STATE_HOMING) {
        if (rocket_speed < maxspeed) {
            rocket_accel *= accel_rate;
            rocket_speed += rocket_accel;
        } else {
            rocket_speed = maxspeed;
        }

        old_pos = rocket_pos;
        rocket_vel.x = rocket_speed * rocket_dir.x;
        rocket_vel.y = rocket_speed * rocket_dir.y;

        rocket_pos.x += rocket_vel.x;
        rocket_pos.y += rocket_vel.y;

        sim->objGrid->ENTITY_Move(rocket_pos, this);
        sim->segGrid->GatherCellContentsFromWorldspaceRegion(min(old_pos.x, rocket_pos.x), min(old_pos.y, rocket_pos.y), max(old_pos.x, rocket_pos.x), max(old_pos.y, rocket_pos.y), nearSegs);

        hit_pos.x = 0;
        hit_pos.y = 0;
        hit_n.x = 0;
        hit_n.y = 0;

        double best_t = 2.0;
        for (size_t i = 0; i < nearSegs.size(); ++i) {
            Segment* segment = nearSegs[i];
            double curr_t = segment->IntersectWithRay(old_pos, rocket_vel, 0, hit_pos, hit_n);

            if (curr_t == -1) {
                Event_Explode(sim);
                return;
            }

            if (curr_t < best_t) {
                best_t = curr_t;
            }
        }

        if (best_t < 2.0) {
            Event_Explode(sim);
            return;
        }

        if (!sim->playerList[targetIndex]->IsDead()) {
            double rocketVelX = rocket_vel.x * prediction_scale;
            double rocketVelY = rocket_vel.y * prediction_scale;
            double ninjaVelX = sim->playerList[targetIndex]->GetVel().x * prediction_scale;
            double ninjaVelY = sim->playerList[targetIndex]->GetVel().y * prediction_scale;

            double rocketPosX = rocket_pos.x + rocketVelX;
            double rocketPosY = rocket_pos.y + rocketVelY;
            double ninjaPosX = sim->playerList[targetIndex]->GetPos().x + ninjaVelX;
            double ninjaPosY = sim->playerList[targetIndex]->GetPos().y + ninjaVelY;

            double deltaX = ninjaPosX - rocketPosX;
            double deltaY = ninjaPosY - rocketPosY;
            double distanceSquared = deltaX * deltaX + deltaY * deltaY;

            if (distanceSquared != 0) {
                deltaX /= sqrt(distanceSquared);
                deltaY /= sqrt(distanceSquared);
                double variable = -rocket_dir.y * deltaX + rocket_dir.x * deltaY;

                rocket_dir.x += turn_rate * variable * (-rocket_dir.y);
                rocket_dir.y += turn_rate * variable * rocket_dir.x;

                double rocketDirMagnitude = rocket_dir.Len();
                if (rocketDirMagnitude == 0) {
                    rocket_dir.x = 0;
                    rocket_dir.y = 0;
                } else {
                    rocket_dir.Scale(1 / rocketDirMagnitude);
                }
            }
        }
        //sim->HACKY_GetParticleManager().Spawn_RocketSmoke(rocket_pos, atan2(rocket_dir.y, rocket_dir.x) / M_PI * 180);
    }
}

void Entity_Rocket::Event_Explode(Simulator* sim) {
    sim->objGrid->ENTITY_Remove(this);
    CUR_STATE = STATE_IDLE;
    targetIndex = -1;
    //sim->HACKY_GetParticleManager().Spawn_Explosion(rocket_pos);
}

EntityGraphics* Entity_Rocket::GenerateGraphicComponent() {
    return new EntityGraphics_Rocket(this, pos.x, pos.y);
}

void Entity_Rocket::GFX_UpdateState(EntityGraphics_Rocket* graphic) {
    if (gfx_PREV_STATE == STATE_PREFIRE && CUR_STATE == STATE_HOMING) {
        graphic->anim_base = EntityGraphics_Rocket::ANIM_FIRE;
    }
    else if (gfx_PREV_STATE == STATE_HOMING && CUR_STATE != STATE_HOMING) {
        graphic->is_rocket_active = false;
        graphic->anim_base = EntityGraphics_Rocket::ANIM_EXPLODE;
    }
    else if (CUR_STATE == STATE_PREFIRE || CUR_STATE == STATE_IDLE) {
        graphic->is_rocket_active = false;
        graphic->anim_base = EntityGraphics_Rocket::ANIM_IDLE;
    }
    if (CUR_STATE == STATE_HOMING) {
        graphic->is_rocket_active = true;
        graphic->pos_rocket.x = rocket_pos.x;
        graphic->pos_rocket.y = rocket_pos.y;
        graphic->orn_rocket = atan2(rocket_dir.y, rocket_dir.x);
    }
}

void Entity_Rocket::Debug_Draw(SimpleRenderer& rend) {
    //rend.SetStyle(0, 0, 100);
    //rend.DrawCircle(pos.x, pos.y, 4);

    if (CUR_STATE == STATE_PREFIRE) {
        //rend.DrawSquare(pos.x, pos.y, 4);
    }
    else {
        //rend.DrawSquare(pos.x, pos.y, 2);
        if (CUR_STATE == STATE_HOMING) {
            //rend.DrawLine(rocket_pos.x, rocket_pos.y, rocket_pos.x - 4 * rocket_dir.x, rocket_pos.y - 4 * rocket_dir.y);
        }
    }
}

// ByteArray Entity_Rocket::saveState() {
//     ByteArray state;
//     state.writeByte(edat::STRUCTTYPE_ROCKET);
//     state.writeDouble(pos.x);
//     state.writeDouble(pos.y);
//     state.writeDouble(rocket_pos.x);
//     state.writeDouble(rocket_pos.y);
//     state.writeDouble(rocket_dir.x);
//     state.writeDouble(rocket_dir.y);
//     state.writeDouble(rocket_speed);
//     state.writeDouble(rocket_accel);
//     state.writeDouble(shot_timer);
//     state.writeInt(CUR_STATE);
//     state.writeInt(targetIndex);
//     state.writeInt(gfx_PREV_STATE);
//     return state;
// }

void Entity_Rocket::saveState(entitySave& state) {
    Entity_Base::saveState(state);
    state.etype = edat::ETYPE_ROCKET;
    state.pos = pos;
    state.pos2 = rocket_pos;
    state.dir = rocket_dir;
    state.vel.x = rocket_speed;
    state.vel.y = rocket_accel;
    state.timer3 = shot_timer;
    state.state = CUR_STATE;
    state.index = targetIndex;
    state.extra = gfx_PREV_STATE;
}