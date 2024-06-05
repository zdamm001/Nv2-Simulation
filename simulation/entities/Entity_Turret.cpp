#include "Entity_Turret.h"
#include "..\\..\\audiovisual\\entitygraphics\\EntityGraphics_Turret.h"

Entity_Turret::Entity_Turret(Grid_Entity* entities, double x, double y)
    : pos(x, y), aim_pos(x, y), aim_region(0), shot_timer(0), CUR_STATE(STATE_IDLE), targetIndex(-1), gfx_triggerEvent(false), HACKY_drawtimer(0), threshold2(3), aimspeed(4), timerstep(4) {
    timer_firetime = 60 * (sim_globals::sim_rate / 40);
    prefire_delay = 10 * (sim_globals::sim_rate / 40);
    postfire_delay = 10 * (sim_globals::sim_rate / 40);

    threshold2[0] = 9216;
    threshold2[1] = 1764;
    threshold2[2] = 576;

    aimspeed[0] = 0.03 * (40 / sim_globals::sim_rate);
    aimspeed[1] = 0.035 * (40 / sim_globals::sim_rate);
    aimspeed[2] = 0.05 * (40 / sim_globals::sim_rate);
    aimspeed[3] = 0.05 * (40 / sim_globals::sim_rate);

    timerstep[0] = 0;
    timerstep[1] = 0.5;
    timerstep[2] = 1.5;
    timerstep[3] = 3.5;

    prediction_scale = sim_globals::sim_rate / 40;
}

Entity_Turret::Entity_Turret(Grid_Entity* entities, entitySave& entity)
    : Entity_Turret(entities, entity.pos.x, entity.pos.y) {
    aim_pos = entity.pos2;
    aim_region = entity.extra;
    shot_timer = entity.timer3;
    CUR_STATE = entity.state;
    targetIndex = entity.index;
}

void Entity_Turret::Think(Simulator* sim) {
    TEMP_hit_pos.x = 0;
    TEMP_hit_pos.y = 0;
    TEMP_hit_n.x = 0;
    TEMP_hit_n.y = 0;

    if (CUR_STATE == STATE_IDLE) {
        int ninjaID = entity_helpers::TryToAquireTarget(pos, sim->playerList, sim->segGrid);
        if (ninjaID >= 0) {
            Event_StartTargetting(ninjaID);
        }
    } else {
        if (targetIndex < 0) {
            return;
        }
        if (CUR_STATE == STATE_TARGETING) {
            if (!IsCurrentTargetVisible(sim, TEMP_hit_pos, TEMP_hit_n)) {
                Event_StartIdling();
            } else {
                UpdateAim(sim->playerList[targetIndex]->GetPos(), sim->playerList[targetIndex]->GetVel());
                if (shot_timer > timer_firetime) {
                    Event_StartFiring();
                }
            }
        }
        else if (CUR_STATE == STATE_PREFIRE) {
            ++shot_timer;
            if (prefire_delay <= shot_timer) {
                if (!sim->playerList[targetIndex]->IsDead()) {
                    double aimDeltaX = aim_pos.x - pos.x;
                    double aimDeltaY = aim_pos.y - pos.y;
                    double distToAim = sqrt(aimDeltaX * aimDeltaX + aimDeltaY * aimDeltaY);
                    aimDeltaX /= distToAim;
                    aimDeltaY /= distToAim;
                    double hitDist = sim->segGrid->GetRaycastDistance(pos.x, pos.y, aimDeltaX, aimDeltaY, HACKY_hit_pos, HACKY_hit_n);
                    for (int i = 0; i < sim->playerList.size(); ++i) {
                        if (!sim->playerList[i]->IsDead()) {
                            vec2 ninjaPos = sim->playerList[i]->GetPos();
                            double ninjaRadius = sim->playerList[i]->GetRadius();
                            if (colutils::Overlap_Circle_Vs_Segment(ninjaPos, ninjaRadius, pos, HACKY_hit_pos, hitDist)) {
                                double ninjaDeltaX = ninjaPos.x - pos.x;
                                double ninjaDeltaY = ninjaPos.y - pos.y;
                                double _loc12_ = aimDeltaX * ninjaDeltaX + aimDeltaY * ninjaDeltaY;
                                HACKY_hit_pos.x = pos.x + _loc12_ * aimDeltaX;
                                HACKY_hit_pos.y = pos.y + _loc12_ * aimDeltaY;
                                HACKY_hit_n.x = 0;
                                HACKY_hit_n.y = 0;
                                sim->Event_PlayerWasKilled(sim->playerList[i], sim_globals::ENEMYTYPE_TURRET, HACKY_hit_pos.x, HACKY_hit_pos.y, aimDeltaX * 8, aimDeltaY * 8);
                            }
                            HACKY_drawtimer = 10;
                        }
                    }
                    //sim->HACKY_GetParticleManager()->Spawn_TurretBullet(pos, HACKY_hit_pos);
                    gfx_triggerEvent = true;
                }
                Event_StopFiring();
            }
        }
        else if (CUR_STATE == STATE_POSTFIRE) {
            ++shot_timer;
            if (postfire_delay <= shot_timer) {
                if (IsCurrentTargetVisible(sim, TEMP_hit_pos, TEMP_hit_n)) {
                    Event_ResumeTargetting();
                } else {
                    Event_StartIdling();
                }
            }
        }
    }
}

void Entity_Turret::Event_StartIdling() {
    CUR_STATE = STATE_IDLE;
    targetIndex = -1;
}

void Entity_Turret::Event_StartTargetting(int ninjaID) {
    aim_pos.Copy(pos);
    shot_timer = 0;
    CUR_STATE = STATE_TARGETING;
    targetIndex = ninjaID;
}

void Entity_Turret::Event_ResumeTargetting() {
    shot_timer = 0;
    CUR_STATE = STATE_TARGETING;
}

void Entity_Turret::Event_StartFiring() {
    shot_timer = 0;
    CUR_STATE = STATE_PREFIRE;
}

void Entity_Turret::Event_StopFiring() {
    shot_timer = 0;
    CUR_STATE = STATE_POSTFIRE;
}

bool Entity_Turret::IsCurrentTargetVisible(Simulator* sim, vec2& hitPos, vec2& hitNormal) {
    Ninja* ninja = sim->playerList[targetIndex];
    bool isVisible = false;
    if (!ninja->IsDead()) {
        isVisible = sim->segGrid->RaycastVsPlayer(pos, ninja->GetPos(), ninja->GetRadius(), hitPos, hitNormal);
    }
    return isVisible;
}

void Entity_Turret::UpdateAim(const vec2& ninjaPos, const vec2& ninjaVel) {
    double velScaleX = ninjaVel.x * prediction_scale;
    double velScaleY = ninjaVel.y * prediction_scale;
    double predictedX = ninjaPos.x + velScaleX;
    double predictedY = ninjaPos.y + velScaleY;
    double deltaX = predictedX - aim_pos.x;
    double deltaY = predictedY - aim_pos.y;
    double distanceSquared = deltaX * deltaX + deltaY * deltaY;
    aim_region = 0;
    for (int i = 0; i < threshold2.size(); ++i) {
        if (distanceSquared > threshold2[i]) {
            break;
        }
        ++aim_region;
    }
    shot_timer += timerstep[aim_region];
    aim_pos.x += aimspeed[aim_region] * deltaX;
    aim_pos.y += aimspeed[aim_region] * deltaY;
}

EntityGraphics* Entity_Turret::GenerateGraphicComponent() {
    return new EntityGraphics_Turret(this, pos.x, pos.y);
}

void Entity_Turret::GFX_UpdateState(EntityGraphics_Turret* graphic) {
    graphic->pos_crosshair.x = aim_pos.x;
    graphic->pos_crosshair.y = aim_pos.y;
    if (gfx_triggerEvent) {
        graphic->anim_base = EntityGraphics_Turret::ANIM_FIRING;
        gfx_triggerEvent = false;
    } else if (CUR_STATE == STATE_IDLE) {
        graphic->anim_base = EntityGraphics_Turret::ANIM_IDLE;
        graphic->anim_crosshair = EntityGraphics_Turret::CROSSHAIR_OFF;
    } else if (CUR_STATE == STATE_PREFIRE) {
        graphic->anim_base = EntityGraphics_Turret::ANIM_PREFIRE;
        graphic->anim_crosshair = EntityGraphics_Turret::CROSSHAIR_PREFIRE;
    } else if (CUR_STATE == STATE_POSTFIRE) {
        graphic->anim_base = EntityGraphics_Turret::ANIM_POSTFIRE;
        graphic->anim_crosshair = EntityGraphics_Turret::CROSSHAIR_POSTFIRE;
    } else if (CUR_STATE == STATE_TARGETING) {
        if (aim_region == 0) {
            graphic->anim_crosshair = EntityGraphics_Turret::CROSSHAIR_FAR;
        } else if (aim_region == 1) {
            graphic->anim_crosshair = EntityGraphics_Turret::CROSSHAIR_MID;
        } else if (aim_region == 2) {
            graphic->anim_crosshair = EntityGraphics_Turret::CROSSHAIR_NEAR;
        }
    }
}

void Entity_Turret::Debug_Draw(SimpleRenderer& rend) {
    //rend.SetStyle(0, 0, 100);
    //rend.DrawCircle(pos.x, pos.y, 4);
    //rend.DrawCross(pos.x, pos.y, 2);
    if (CUR_STATE != STATE_IDLE) {
        if (CUR_STATE == STATE_TARGETING) {
            if (aim_region == 0) {
                //rend.SetStyle(0, 0, 50);
                //rend.DrawPlus(aim_pos.x, aim_pos.y, 2);
            } else if (aim_region == 1) {
                //rend.SetStyle(0, 0, 75);
                //rend.DrawPlus(aim_pos.x, aim_pos.y, 3);
            } else if (aim_region > 1) {
                //rend.SetStyle(0, 0, 100);
                //rend.DrawPlus(aim_pos.x, aim_pos.y, 4);
            }
        } else if (CUR_STATE == STATE_PREFIRE) {
            //rend.DrawSquare(aim_pos.x, aim_pos.y, 4);
        } else if (CUR_STATE == STATE_POSTFIRE) {
            //rend.DrawCircle(aim_pos.x, aim_pos.y, 2);
        }
        //rend.SetStyle(0, 0, 10);
        //rend.DrawLine(pos.x, pos.y, aim_pos.x, aim_pos.y);
    }
    if (HACKY_drawtimer > 0) {
        //rend.SetStyle(0, 0, 100 * (static_cast<double>(HACKY_drawtimer) / 10));
        //rend.DrawLine(pos.x, pos.y, HACKY_hit_pos.x, HACKY_hit_pos.y);
        //rend.DrawLine(HACKY_hit_pos.x, HACKY_hit_pos.y, HACKY_hit_pos.x + 4 * HACKY_hit_n.x, HACKY_hit_pos.y + 4 * HACKY_hit_n.y);
        --HACKY_drawtimer;
    }
}

// ByteArray Entity_Turret::saveState() {
//     ByteArray state;
//     state.writeByte(edat::STRUCTTYPE_TURRET);
//     state.writeDouble(pos.x);
//     state.writeDouble(pos.y);
//     state.writeDouble(aim_pos.x);
//     state.writeDouble(aim_pos.y);
//     state.writeInt(aim_region);
//     state.writeDouble(shot_timer);
//     state.writeInt(CUR_STATE);
//     state.writeInt(targetIndex);
//     return state;
// }

void Entity_Turret::saveState(entitySave& state) {
    Entity_Base::saveState(state);
    state.etype = edat::ETYPE_TURRET;
    state.pos = pos;
    state.pos2 = aim_pos;
    state.extra = aim_region;
    state.timer3 = shot_timer;
    state.state = CUR_STATE;
    state.index = targetIndex;
}