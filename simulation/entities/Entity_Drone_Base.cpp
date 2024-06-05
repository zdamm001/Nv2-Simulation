#include "Entity_Drone_Base.h"

vector<vec2> Entity_Drone_Base::DIR_TO_VEC2(4);
vector<double> Entity_Drone_Base::DIR_TO_RAD(4);
vector<vector<unsigned int>> Entity_Drone_Base::MOVELIST(4, vector<unsigned int>(4));

Entity_Drone_Base::Entity_Drone_Base(Grid_Entity* entities, double x, double y, double speed, unsigned int facingDir, unsigned int moveType)
    : pos(x, y), r(12.0 * (3.0 / 4.0)), speed(speed), step_size(24), next_goal(pos), facing_DIR(facingDir), move_TYPE(moveType), gfxorn(DIR_TO_RAD[facingDir]) {
    entities->ENTITY_Add(pos, this);
}

Entity_Drone_Base::Entity_Drone_Base(Grid_Entity* entities, entitySave& entity, double speed)
    : pos(entity.pos), r(12.0 * (3.0 / 4.0)), speed(speed), step_size(24), next_goal(entity.pos2), facing_DIR(entity.facingDir), move_TYPE(entity.moveType), gfxorn(entity.timer3) {
    entities->ENTITY_Add(pos, this);
}

void Entity_Drone_Base::Initialize() {
    DIR_TO_VEC2[DIR_R] = vec2( 1, 0);
    DIR_TO_VEC2[DIR_D] = vec2( 0, 1);
    DIR_TO_VEC2[DIR_L] = vec2(-1, 0);
    DIR_TO_VEC2[DIR_U] = vec2( 0,-1);
    DIR_TO_RAD[DIR_R] = 0 * M_PI;
    DIR_TO_RAD[DIR_D] = 0.5 * M_PI;
    DIR_TO_RAD[DIR_L] = 1 * M_PI;
    DIR_TO_RAD[DIR_U] = 1.5 * M_PI;
    MOVELIST[MOVETYPE_SURFACE_CW][0] = ROT_90;
    MOVELIST[MOVETYPE_SURFACE_CW][1] = ROT_0;
    MOVELIST[MOVETYPE_SURFACE_CW][2] = ROT_270;
    MOVELIST[MOVETYPE_SURFACE_CW][3] = ROT_180;
    MOVELIST[MOVETYPE_SURFACE_CCW][0] = ROT_270;
    MOVELIST[MOVETYPE_SURFACE_CCW][1] = ROT_0;
    MOVELIST[MOVETYPE_SURFACE_CCW][2] = ROT_90;
    MOVELIST[MOVETYPE_SURFACE_CCW][3] = ROT_180;
    MOVELIST[MOVETYPE_WANDER_CW][0] = ROT_0;
    MOVELIST[MOVETYPE_WANDER_CW][1] = ROT_90;
    MOVELIST[MOVETYPE_WANDER_CW][2] = ROT_270;
    MOVELIST[MOVETYPE_WANDER_CW][3] = ROT_180;
    MOVELIST[MOVETYPE_WANDER_CCW][0] = ROT_0;
    MOVELIST[MOVETYPE_WANDER_CCW][1] = ROT_270;
    MOVELIST[MOVETYPE_WANDER_CCW][2] = ROT_90;
    MOVELIST[MOVETYPE_WANDER_CCW][3] = ROT_180;
}

void Entity_Drone_Base::Move(Simulator* sim) {
    Move_Forward(sim->edgeGrid, sim->segGrid, sim->objGrid, sim->playerList);
    double facingAngle = DIR_TO_RAD[facing_DIR];
    double angleDiff = mathutils::WrapAngle_Shortest(facingAngle - gfxorn);
    gfxorn = mathutils::WrapAngle_Pos(gfxorn + 0.3 * angleDiff);
}

void Entity_Drone_Base::Move_Forward(Grid_Edges* edges, Grid_Segment* segs, Grid_Entity* entities, const vector<Ninja*>& players) {
    double velX = DIR_TO_VEC2[facing_DIR].x * speed;
    double velY = DIR_TO_VEC2[facing_DIR].y * speed;
    double newPositionX = pos.x + velX;
    double newPositionY = pos.y + velY;
    double distToGoalX = next_goal.x - pos.x;
    double distToGoalY = next_goal.y - pos.y;
    double newDistToGoalX = next_goal.x - newPositionX;
    double newDistToGoalY = next_goal.y - newPositionY;
    double distToGoal = sqrt(distToGoalX * distToGoalX + distToGoalY * distToGoalY);
    double dpPassedGoal = distToGoalX * newDistToGoalX + distToGoalY * newDistToGoalY;

    if (distToGoal < 0.000001 || dpPassedGoal < 0) {
        pos = next_goal;
        if (ChooseNextDirAndGoal(edges, players)) {
            double remainingSpeed = max(0.0, speed - distToGoal);
            vec2 moveDirection = DIR_TO_VEC2[facing_DIR];
            pos.x += moveDirection.x * remainingSpeed;
            pos.y += moveDirection.y * remainingSpeed;
        }
    } else {
        pos.x += velX;
        pos.y += velY;
    }

    entities->ENTITY_Move(pos, this);
}

bool Entity_Drone_Base::ChooseNextDirAndGoal(Grid_Edges* edges, const vector<Ninja*>& ninjas) {
    for (int i = 0; i < 4; ++i) {
        int newDirection = (facing_DIR + MOVELIST[move_TYPE][i]) % 4;
        if (ChooseNextDirAndGoal_HELPER_TestDir(edges, newDirection, next_goal)) {
            facing_DIR = newDirection;
            return true;
        }
    }
    return false;
}

bool Entity_Drone_Base::ChooseNextDirAndGoal_HELPER_TestDir(Grid_Edges* edges, unsigned int direction, vec2& nextGoal) {
    vec2 dir = DIR_TO_VEC2[direction];
    double newGoalX = pos.x + dir.x * step_size;
    double newGoalY = pos.y + dir.y * step_size;

    if (dir.y == 0) {
        int minYCoord = edges->GetGridCoordinateFromWorldspace_1D(pos.y - r);
        int maxYCoord = edges->GetGridCoordinateFromWorldspace_1D(pos.y + r);
        int currentXCoord = edges->GetGridCoordinateFromWorldspace_1D(pos.x + dir.x * r);
        int newGoalXCoord = edges->GetGridCoordinateFromWorldspace_1D(newGoalX + dir.x * r);

        if (!edges->ScanHorizontal_Directed(minYCoord, maxYCoord, currentXCoord, newGoalXCoord, dir.x)) {
            return false;
        }
    } else {
        if (dir.x != 0) {
            return false;
        }
        int minXCoord = edges->GetGridCoordinateFromWorldspace_1D(pos.x - r);
        int maxXCoord = edges->GetGridCoordinateFromWorldspace_1D(pos.x + r);
        int currentYCoord = edges->GetGridCoordinateFromWorldspace_1D(pos.y + dir.y * r);
        int newGoalYCoord = edges->GetGridCoordinateFromWorldspace_1D(newGoalY + dir.y * r);

        if (!edges->ScanVertical_Directed(minXCoord, maxXCoord, currentYCoord, newGoalYCoord, dir.y)) {
            return false;
        }
    }

    nextGoal.x = newGoalX;
    nextGoal.y = newGoalY;
    return true;
}


void Entity_Drone_Base::Debug_Draw(SimpleRenderer& rend) {
    //rend.SetStyle(0, 0, 100);
    //rend.DrawCircle(pos.x, pos.y, r);
    vec2 dir(cos(gfxorn), sin(gfxorn));
    //rend.DrawLine(pos.x, pos.y, pos.x + dir.x * 8, pos.y + dir.y * 8);
}

void Entity_Drone_Base::saveState(entitySave& state) {
    Entity_Base::saveState(state);
    state.pos = pos;
    state.timer3 = gfxorn;
    state.pos2 = next_goal;
    state.facingDir = facing_DIR;
    state.moveType = move_TYPE;
}