#include "Entity_FloorGuard.h"

Entity_FloorGuard::Entity_FloorGuard(Grid_Entity& entities, double x, double y)
    : pos(x, y),
      speed(12 * (3 / 7) * (40 / sim_globals::sim_rate)),
      r(12 * 0.5),
      CUR_STATE(0),
      margin(0) {
    entities.ENTITY_Add(pos, this);
}

bool Entity_FloorGuard::CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) {
    if (colutils::Overlap_Circle_Vs_Circle(pos, r, circlePosition, circleRadius)) {
        double deltaX = circlePosition.x - pos.x;
        double deltaY = circlePosition.y - pos.y;
        double distance = sqrt(deltaX * deltaX + deltaY * deltaY);
        deltaX /= distance;
        deltaY /= distance;
        //sim->HACKY_GetParticleManager().Spawn_Zap(pos.x + deltaX * r, pos.y + deltaY * r, atan2(deltaY, deltaX) / M_PI * 180);
        if (ninja == nullptr) {
            result.vec_x = deltaX * 10;
            result.vec_y = deltaY * 10;
            return true;
        }
        sim->Event_PlayerWasKilled(ninja, sim_globals::ENEMYTYPE_FLOORGUARD, circlePosition.x - deltaX * circleRadius, circlePosition.y - deltaY * circleRadius, deltaX * 10, deltaY * 10);
    }
    return false;
}

void Entity_FloorGuard::Think(Simulator* sim) {
    if (CUR_STATE == 0) {
        for (int i = 0; i < sim->playerList.size(); ++i) {
            Ninja* ninja = sim->playerList[i];
            if (!ninja->IsDead()) {
                vec2 ninjaPos = ninja->GetPos();
                double guardYMin = pos.y + r;
                double guardYMax = guardYMin - 24;
                if (ninjaPos.y >= guardYMax && ninjaPos.y <= guardYMin) {
                    int ninjaX = sim->edgeGrid.GetGridCoordinateFromWorldspace_1D(ninjaPos.x);
                    int guardX = sim->edgeGrid.GetGridCoordinateFromWorldspace_1D(pos.x);
                    int guardY = sim->edgeGrid.GetGridCoordinateFromWorldspace_1D(pos.y);
                    int state = 0;
                    if (sim->edgeGrid.ScanHorizontal(guardY, guardY, guardX, ninjaX)) {
                        state = 1;
                        if (ninjaPos.x < pos.x) {
                            state = -1;
                        }
                    }
                    if (state != 0) {
                        CUR_STATE = state;
                        break;
                    }
                }
            }
        }
    }
}

void Entity_FloorGuard::Move(Simulator* sim) {
    if (CUR_STATE == 0) {
        return;
    }
    
    double radius = r + margin;
    double newPos = pos.x + CUR_STATE * speed;
    double radiusInMoveDir = CUR_STATE * radius;
    
    int currX = sim->edgeGrid.GetGridCoordinateFromWorldspace_1D(pos.x + radiusInMoveDir);
    int newX = sim->edgeGrid.GetGridCoordinateFromWorldspace_1D(newPos + radiusInMoveDir);
    
    if (currX != newX) {
        int guardY = sim->edgeGrid.GetGridCoordinateFromWorldspace_1D(pos.y);
        
        if (!sim->edgeGrid.IsEmpty(newX, guardY, CUR_STATE, 0) || !sim->edgeGrid.IsSolid_IgnoreDoors(currX, guardY, 0, 1)) {
            newPos = sim->edgeGrid.GetWorldspaceCoordinateFromGridEdge_1D(newX, CUR_STATE) - CUR_STATE * (radius + 0.01);
            CUR_STATE = 0;
        }
    }
    
    pos.x = newPos;
    sim->objGrid.ENTITY_Move(pos, this);
}

EntityGraphics* Entity_FloorGuard::GenerateGraphicComponent() {
    //return new EntityGraphics_FloorGuard(this);
}

void Entity_FloorGuard::GFX_UpdateState(EntityGraphics_FloorGuard* graphic) {
    //graphic->pos.x = pos.x;
    //graphic->pos.y = pos.y;
    if (CUR_STATE == 0) {
        //graphic->anim = EntityGraphics_FloorGuard::ANIM_IDLE;
    }
    else if (CUR_STATE == -1) {
        //graphic->anim = EntityGraphics_FloorGuard::ANIM_CHASE_L;
    }
    else {
        //graphic->anim = EntityGraphics_FloorGuard::ANIM_CHASE_R;
    }
}

void Entity_FloorGuard::Debug_Draw(SimpleRenderer& rend) {
    //rend.SetStyle(0, 0, 100);
    //rend.DrawCircle(pos.x, pos.y, r);
    if (CUR_STATE != 0) {
        //rend.DrawLine(pos.x, pos.y, pos.x + CUR_STATE * 8, pos.y);
    }
}
