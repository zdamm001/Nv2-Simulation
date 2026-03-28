#include "Entity_Thwomp.h"
#include "..\\..\\audiovisual\\entitygraphics\\EntityGraphics_Thwomp.h"

Entity_Thwomp::Entity_Thwomp(Grid_Entity* entities, double x, double y, int fallDir, bool isHorizontal)
    : pos(x, y), anchor(x, y), r(12 * (3.0 / 4.0)), fallspeed(12 * (5.0 / 14.0) * (40.0 / sim_globals::sim_rate)), raisespeed(12 * (1.0 / 7.0) * (40.0 / sim_globals::sim_rate)), CUR_STATE(0), falldir(fallDir), isHorizontal(isHorizontal) {
    entities->ENTITY_Add(pos, this);
    n = vec2();
}

Entity_Thwomp::Entity_Thwomp(Grid_Entity* entities, entitySave& entity)
    : pos(entity.pos), anchor(entity.pos2), r(12 * (3.0 / 4.0)), fallspeed(12 * (5.0 / 14.0) * (40.0 / sim_globals::sim_rate)), raisespeed(12 * (1.0 / 7.0) * (40.0 / sim_globals::sim_rate)), CUR_STATE(entity.state), falldir(entity.extra), isHorizontal(entity.is2) {
    entities->ENTITY_Add(pos, this);
    n = entity.n;
}

bool Entity_Thwomp::CollideVsCircle_Physical(collision_result_physical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius) {
    n.x = 0;
    n.y = 0;
    double penetration = colutils::Penetration_Square_vs_Point(pos, r + circleRadius, circlePosition, n);
    if (penetration != 0) {
        result.isHardCollision = false;
        result.nx = n.x;
        result.ny = n.y;
        result.pen = penetration;
        return true;
    }
    return false;
}

bool Entity_Thwomp::CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) {
    epsilon = 0.1;
    n.x = 0;
    n.y = 0;
    double penetration = colutils::Penetration_Square_vs_Point(pos, epsilon + r + circleRadius, circlePosition, n);
    if (penetration != 0) {
        if ((isHorizontal && n.x * falldir > 0) || (!isHorizontal && n.y * falldir > 0)) {
            if (isHorizontal) {
                //sim->HACKY_GetParticleManager()->Spawn_ZapThwompH(pos, r * falldir, r);
            } else {
                //sim->HACKY_GetParticleManager()->Spawn_ZapThwompV(pos, r, r * falldir);
            }
            if (ninja == nullptr) {
                result.vec_x = n.x * 8;
                result.vec_y = n.y * 8 - 4;
                return true;
            }
            sim->Event_PlayerWasKilled(ninja, sim_globals::ENEMYTYPE_THWOMP, circlePosition.x - n.x * circleRadius, circlePosition.y - n.y * circleRadius, n.x * 8, n.y * 8 - 4);
        } else if (ninja != nullptr) {
            result.vec_x = n.x;
            result.vec_y = n.y;
            return true;
        }
    }
    return false;
}

void Entity_Thwomp::Think(Simulator* sim) {
    if (CUR_STATE == 0) {
        Grid_Edges* edgeGrid = sim->edgeGrid;
        for (size_t i = 0; i < sim->playerList.size(); i++) {
            Ninja* ninja = sim->playerList[i];
            if (!ninja->IsDead()) {
                vec2 ninjaPos = ninja->GetPos();
                double ninjaRadius = ninja->GetRadius();
                double deltaX = ninjaPos.x - pos.x;
                double deltaY = ninjaPos.y - pos.y;
                double detectionRange = 2 * (r + ninjaRadius);
                if (isHorizontal) {
                    if (fabs(deltaY) < detectionRange) {
                        int thwompX = edgeGrid->GetGridCoordinateFromWorldspace_1D(pos.x - falldir * r);
                        int thwompYMin = edgeGrid->GetGridCoordinateFromWorldspace_1D(pos.y - r);
                        int thwompYMax = edgeGrid->GetGridCoordinateFromWorldspace_1D(pos.y + r);
                        int thwompEndX = edgeGrid->SweepHorizontal(thwompYMin, thwompYMax, thwompX, falldir);
                        int ninjaX = edgeGrid->GetGridCoordinateFromWorldspace_1D(ninjaPos.x);
                        if (!(ninjaX < min(thwompX, thwompEndX) || ninjaX > max(thwompX, thwompEndX))) {
                            CUR_STATE = 1;
                            break;
                        }
                    }
                } else {
                    if (fabs(deltaX) < detectionRange) {
                        int thwompY = edgeGrid->GetGridCoordinateFromWorldspace_1D(pos.y - falldir * r);
                        int thwompXMin = edgeGrid->GetGridCoordinateFromWorldspace_1D(pos.x - r);
                        int thwompXMax = edgeGrid->GetGridCoordinateFromWorldspace_1D(pos.x + r);
                        int thwompEndY = edgeGrid->SweepVertical(thwompXMin, thwompXMax, thwompY, falldir);
                        int ninjaY = edgeGrid->GetGridCoordinateFromWorldspace_1D(ninjaPos.y);
                        if (!(ninjaY < min(thwompY, thwompEndY) || ninjaY > max(thwompY, thwompEndY))) {
                            CUR_STATE = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void Entity_Thwomp::Move(Simulator* sim) {
    if (CUR_STATE == 0) {
        return;
    }

    Grid_Edges* edgeGrid = sim->edgeGrid;
    int dir = falldir * CUR_STATE;
    double radius = dir * r;
    double speed = (CUR_STATE == -1) ? raisespeed : fallspeed;

    if (isHorizontal) {
        double newX = pos.x + dir * speed;
        if (CUR_STATE == -1 && (pos.x - anchor.x) * (newX - anchor.x) <= 0) {
            newX = anchor.x;
        }
        int oldGridX = edgeGrid->GetGridCoordinateFromWorldspace_1D(pos.x + radius);
        int newGridX = edgeGrid->GetGridCoordinateFromWorldspace_1D(newX + radius);

        if (oldGridX != newGridX) {
            int minY = edgeGrid->GetGridCoordinateFromWorldspace_1D(pos.y - r);
            int maxY = edgeGrid->GetGridCoordinateFromWorldspace_1D(pos.y + r);
            if (!edgeGrid->IsEmpty_Column(oldGridX, minY, maxY, dir)) {
                if (CUR_STATE != -1) {
                    CUR_STATE = -1;
                }
                return;
            }
        }
        
        pos.x = newX;
        sim->objGrid->ENTITY_Move(pos, this);

        if (CUR_STATE == -1 && pos.x == anchor.x) {
            CUR_STATE = 0;
        }
    } else {
        double newY = pos.y + dir * speed;
        if (CUR_STATE == -1 && (pos.y - anchor.y) * (newY - anchor.y) <= 0) {
            newY = anchor.y;
        }
        int oldGridY = edgeGrid->GetGridCoordinateFromWorldspace_1D(pos.y + radius);
        int newGridY = edgeGrid->GetGridCoordinateFromWorldspace_1D(newY + radius);

        if (oldGridY != newGridY) {
            int minX = edgeGrid->GetGridCoordinateFromWorldspace_1D(pos.x - r);
            int maxX = edgeGrid->GetGridCoordinateFromWorldspace_1D(pos.x + r);
            if (!edgeGrid->IsEmpty_Row(oldGridY, minX, maxX, dir)) {
                if (CUR_STATE != -1) {
                    CUR_STATE = -1;
                }
                return;
            }
        }
        
        pos.y = newY;
        sim->objGrid->ENTITY_Move(pos, this);

        if (CUR_STATE == -1 && pos.y == anchor.y) {
            CUR_STATE = 0;
        }
    }
}

EntityGraphics* Entity_Thwomp::GenerateGraphicComponent() {
    double angle = 0.0;
    
    if (isHorizontal) {
        if (falldir < 0) {
            angle = M_PI;
        }
    } else {
        if (falldir < 0) {
            angle = 1.5 * M_PI;
        } else {
            angle = 0.5 * M_PI;
        }
    }
    return new EntityGraphics_Thwomp(this, angle);
}

void Entity_Thwomp::GFX_UpdateState(EntityGraphics_Thwomp* graphic) {
    graphic->pos.x = pos.x;
    graphic->pos.y = pos.y;
}

void Entity_Thwomp::Debug_Draw(SimpleRenderer& rend) {
    //rend.SetStyle(0, 0, 100);
    //rend.DrawSquare(pos.x, pos.y, r);

    for (int i = -4; i <= 4; i += 4) {
        if (isHorizontal) {
            //rend.DrawLine(pos.x + falldir * r - 2, pos.y + i, pos.x + falldir * r + 2, pos.y + i);
        } else {
            //rend.DrawLine(pos.x + i, pos.y + falldir * r - 2, pos.x + i, pos.y + falldir * r + 2);
        }
    }

    if (CUR_STATE != 0) {
        if (isHorizontal) {
            //rend.DrawLine(pos.x, pos.y, pos.x + falldir * CUR_STATE * 8, pos.y);
        } else {
            //rend.DrawLine(pos.x, pos.y, pos.x, pos.y + falldir * CUR_STATE * 8);
        }
    }
}

// ByteArray Entity_Thwomp::saveState() {
//     ByteArray state;
//     state.writeByte(edat::STRUCTTYPE_THWOMP);
//     state.writeDouble(pos.x);
//     state.writeDouble(pos.y);
//     state.writeInt(CUR_STATE);
//     state.writeInt(falldir);
//     state.writeInt(isHorizontal);
//     state.writeDouble(n.x);
//     state.writeDouble(n.y);
//     return state;
// }

void Entity_Thwomp::saveState(entitySave& state) {
    Entity_Base::saveState(state);
    state.etype = edat::ETYPE_THWOMP;
    state.pos = pos;
    state.pos2 = anchor;
    state.state = CUR_STATE;
    state.extra = falldir;
    state.is2 = isHorizontal;
    state.n = n;
}