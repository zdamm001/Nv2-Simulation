#include "Entity_Drone_Chaser.h"

Entity_Drone_Chaser::Entity_Drone_Chaser(Grid_Entity& entities, double x, double y, unsigned int facingDir, unsigned int moveType)
    : Entity_Drone_Zap(entities, x, y, facingDir, moveType),
      isChasing(false),
      speed_regular(speed),
      speed_chasing(speed_regular * 2),
      gfx_startedChasing(false),
      old_chase_DIR(-1) {}

void Entity_Drone_Chaser::Think(Simulator* sim) {

}

void Entity_Drone_Chaser::StartChasing(unsigned int newChaseDir) {
    facing_DIR = newChaseDir;
    speed = speed_chasing;
    isChasing = true;
    gfx_startedChasing = true;
}

void Entity_Drone_Chaser::StopChasing(unsigned int newFacingDir) {
    old_chase_DIR = facing_DIR;
    facing_DIR = newFacingDir;
    speed = speed_regular;
    isChasing = false;
}

bool Entity_Drone_Chaser::ChooseNextDirAndGoal(Grid_Edges& edges, const vector<Ninja*>& playerList) {
    if (isChasing) {
        if (ChooseNextDirAndGoal_HELPER_TestDir(edges, facing_DIR, next_goal)) {
            return true;
        }
        unsigned int newDir = (facing_DIR - MOVELIST[move_TYPE][0] + 4) % 4;
        StopChasing(newDir);
    }

    unsigned int currentDir = facing_DIR;
    if (old_chase_DIR != -1) {
        currentDir = old_chase_DIR;
        old_chase_DIR = -1;
    }

    for (int i = 0; i < playerList.size(); ++i) {
        if (!playerList[i]->IsDead()) {
            vec2 ninjaPos = playerList[i]->GetPos();
            for (int j = -1; j <= 1; j++) {
                unsigned int chaseDir = (currentDir + j + 4) % 4;
                vec2 chaseDirVec = DIR_TO_VEC2[chaseDir];
                double deltaX = ninjaPos.x - pos.x;
                double deltaY = ninjaPos.y - pos.y;
                if (chaseDirVec.x * deltaX + chaseDirVec.y * deltaY > 0) {
                    if (abs(-chaseDirVec.y * deltaX + chaseDirVec.x * deltaY) <= 12) {
                        bool isHorizontal = true;
                        if (chaseDir % 2 == 1) {
                            isHorizontal = false;
                        }
                        int sweepDir = 1;
                        if (chaseDir >= 2) {
                            sweepDir = -1;
                        }
                        if (isHorizontal) {
                            int droneX = edges.GetGridCoordinateFromWorldspace_1D(pos.x);
                            int droneY = edges.GetGridCoordinateFromWorldspace_1D(pos.y);
                            int chaseEndX = edges.SweepHorizontal(droneY, droneY, droneX, sweepDir);
                            int ninjaX = edges.GetGridCoordinateFromWorldspace_1D(ninjaPos.x);
                            if (ninjaX < min(droneX, chaseEndX) || ninjaX > max(droneX, chaseEndX)) {
                                continue;
                            }
                        }
                        else {
                            int droneY = edges.GetGridCoordinateFromWorldspace_1D(pos.y);
                            int droneX = edges.GetGridCoordinateFromWorldspace_1D(pos.x);
                            int chaseEndY = edges.SweepVertical(droneX, droneX, droneY, sweepDir);
                            int ninjaY = edges.GetGridCoordinateFromWorldspace_1D(ninjaPos.y);
                            if (ninjaY < min(droneY, chaseEndY) || ninjaY > max(droneY, chaseEndY)) {
                                continue;
                            }
                        }
                        if (ChooseNextDirAndGoal_HELPER_TestDir(edges, chaseDir, next_goal)) {
                            StartChasing(chaseDir);
                            return true;
                        }
                    }
                }
            }
        }
    }

    return Entity_Drone_Zap::ChooseNextDirAndGoal(edges, playerList);
}

EntityGraphics* Entity_Drone_Chaser::GenerateGraphicComponent() {
    //return new EntityGraphics_Drone_Chaser(this);
}

void Entity_Drone_Chaser::GFX_UpdateState(EntityGraphics_Drone_Chaser* graphic) {
    //graphic->pos.x = pos.x;
    //graphic->pos.y = pos.y;
    //graphic->orn = gfxorn;
    if (this->gfx_startedChasing) {
        this->gfx_startedChasing = false;
        //graphic->anim = EntityGraphics_Drone_Chaser::ANIM_CHASE;
    } else {
        //graphic->anim = EntityGraphics_Drone_Chaser::ANIM_IDLE;
    }
}

void Entity_Drone_Chaser::Debug_Draw(SimpleRenderer& rend) {
    Entity_Drone_Zap::Debug_Draw(rend);
    double antennaX = pos.x + sqrt(0.5) * r;
    double antennaY = pos.y - sqrt(0.5) * r;
    if (isChasing) {
        //rend.SetStyle(2, 0, 100);
    } else {
        //rend.SetStyle(0, 0, 100);
    }
    //rend.DrawLine(antennaX, antennaY, antennaX, antennaY - 8);
}
