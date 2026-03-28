#include "Entity_Drone_Shooter_Base.h"

vec2 Entity_Drone_Shooter_Base::zero_vec = vec2();

Entity_Drone_Shooter_Base::Entity_Drone_Shooter_Base(Grid_Entity* entities, double x, double y, double speed, unsigned int facingDirection, unsigned int moveType, int prefireDelay, int postfireDelay)
    : Entity_Drone_Base(entities, x, y, speed, facingDirection, moveType),
      CUR_FIRING_STATE(FIRING_STATE_IDLE),
      firing_timer(0),
      prefire_delay(prefireDelay),
      postfire_delay(postfireDelay),
      targetIndex(-1) {}

Entity_Drone_Shooter_Base::Entity_Drone_Shooter_Base(Grid_Entity* entities, entitySave& entity, double speed, int prefireDelay, int postfireDelay)
    : Entity_Drone_Base(entities, entity, speed),
      CUR_FIRING_STATE(entity.state),
      firing_timer(entity.timer),
      prefire_delay(prefireDelay),
      postfire_delay(postfireDelay),
      targetIndex(entity.index) {}

void Entity_Drone_Shooter_Base::Move(Simulator* sim) {
    if (CUR_FIRING_STATE == FIRING_STATE_IDLE) {
        Entity_Drone_Base::Move(sim);
    }
}

int Entity_Drone_Shooter_Base::GetFiringState() {
    return CUR_FIRING_STATE;
}

void Entity_Drone_Shooter_Base::Think(Simulator* sim) {
    if (CUR_FIRING_STATE == FIRING_STATE_IDLE) {
        int ninjaID = entity_helpers::TryToAquireTarget(pos, sim->playerList, sim->segGrid);
        if (ninjaID >= 0) {
            Internal_StartPrefiring(sim, ninjaID, sim->playerList[ninjaID]->GetPos());
            return;
        }
    } else {
        if (targetIndex < 0) {
            return;
        }
        if (CUR_FIRING_STATE == FIRING_STATE_PREFIRING) {
            if (sim->playerList[targetIndex]->IsDead()) {
                Internal_StartPostfiring(sim);
            } else {
                Update_Prefiring(sim, sim->playerList[targetIndex]->GetPos());
                ++firing_timer;
                if (prefire_delay <= firing_timer) {
                    Internal_StartFiring(sim, sim->playerList[targetIndex]->GetPos(), sim->playerList[targetIndex]->GetVel());
                }
            }
        } else if (CUR_FIRING_STATE == FIRING_STATE_FIRING) {
            if (Update_Firing(sim)) {
                Internal_StartPostfiring(sim);
            }
        } else if (CUR_FIRING_STATE == FIRING_STATE_POSTFIRING) {
            ++firing_timer;
            if (postfire_delay <= firing_timer) {
                for (size_t i = 0; i < sim->playerList.size(); ++i) {
                    if (!sim->playerList[i]->IsDead()) {
                        if (sim->segGrid->RaycastVsPlayer(pos, sim->playerList[i]->GetPos(), sim->playerList[i]->GetRadius(), zero_vec, zero_vec)) {
                            Internal_StartPrefiring(sim, i, sim->playerList[i]->GetPos());
                            return;
                        }
                    }
                }
                Internal_StartIdling();
            }
        }
    }
}

void Entity_Drone_Shooter_Base::Internal_StartPrefiring(Simulator* sim, int ninjaID, const vec2& ninjaPos) {
    firing_timer = 0;
    CUR_FIRING_STATE = FIRING_STATE_PREFIRING;
    targetIndex = ninjaID;
    Start_Prefiring(sim, ninjaPos);
}

void Entity_Drone_Shooter_Base::Internal_StartFiring(Simulator* sim, const vec2& ninjaPos, const vec2& ninjaVel) {
    CUR_FIRING_STATE = FIRING_STATE_FIRING;
    Start_Firing(sim, ninjaPos, ninjaVel);
}

void Entity_Drone_Shooter_Base::Internal_StartPostfiring(Simulator* sim) {
    firing_timer = 0;
    CUR_FIRING_STATE = FIRING_STATE_POSTFIRING;
    Start_Postfiring(sim);
}

void Entity_Drone_Shooter_Base::Internal_StartIdling() {
    CUR_FIRING_STATE = FIRING_STATE_IDLE;
    targetIndex = -1;
}

void Entity_Drone_Shooter_Base::Start_Prefiring(Simulator* sim, const vec2& ninjaPos) { }

void Entity_Drone_Shooter_Base::Update_Prefiring(Simulator* sim, const vec2& ninjaPos) { }

void Entity_Drone_Shooter_Base::Start_Firing(Simulator* sim, const vec2& ninjaPos, const vec2& ninjaVel) { }

bool Entity_Drone_Shooter_Base::Update_Firing(Simulator* sim) {return true;}

void Entity_Drone_Shooter_Base::Start_Postfiring(Simulator* sim) { }

void Entity_Drone_Shooter_Base::Debug_Draw(SimpleRenderer& rend) {
    Entity_Drone_Base::Debug_Draw(rend);
    //rend.SetStyle(0, 0, 100);
    if (CUR_FIRING_STATE == FIRING_STATE_PREFIRING) {
        double prefiringProgress = double(firing_timer) / prefire_delay;
        //rend.DrawSquare(pos.x, pos.y, r * prefiringProgress);
    } else if (CUR_FIRING_STATE == FIRING_STATE_POSTFIRING) {
        double postfiringProgress = 1 - double(firing_timer) / postfire_delay;
        //rend.DrawSquare(pos.x, pos.y, r * postfiringProgress);
    }
}

void Entity_Drone_Shooter_Base::saveState(entitySave& state) {
    Entity_Drone_Base::saveState(state);
    state.timer = firing_timer;
    state.state = CUR_FIRING_STATE;
    state.index = targetIndex;
}