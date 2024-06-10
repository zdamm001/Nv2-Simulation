#include "Ragdoll.h"

const vector<double> Ragdoll::pRadius = {2.49, 2.49, 1.99, 1.99, 2.99, 2.99};
const vector<double> Ragdoll::pDrag = {0.99, 0.995, 0.995, 0.99, 0.99, 0.995};
const vector<double> Ragdoll::sWeight = {0.4, 0.2, 0.26, 0.32, 0.37};
const vector<double> Ragdoll::sMinRatio = {0.8, 0.6, 0.6, 0.6, 0.6};
const vector<double> Ragdoll::sMaxLen = {30 * hacky_scale, 40 * hacky_scale, 40 * hacky_scale, 60 * hacky_scale, 60 * hacky_scale};

const vector<vec2> Ragdoll::debugpose_pos = {
    vec2(0, -sMaxLen[0]),
    vec2(0, 0),
    vec2(sMaxLen[1], -sMaxLen[0]),
    vec2(-sMaxLen[2], -sMaxLen[0]),
    vec2(sqrt(0.5) * sMaxLen[3], sqrt(0.5) * sMaxLen[3]),
    vec2(-sqrt(0.5) * sMaxLen[4], sqrt(0.5) * sMaxLen[3])
};

const vector<vec2> Ragdoll::debugpose_vel(6, vec2(0, 0));

Ragdoll::Ragdoll() : cur_state(STATE_UNEXPLODED), explosion_accumulator(0) {
    pList.resize(2);
    pList[STATE_UNEXPLODED].resize(6);
    pList[STATE_UNEXPLODED][0] = new RagParticle(pRadius[0], pDrag[0]);
    pList[STATE_UNEXPLODED][1] = new RagParticle(pRadius[1], pDrag[1]);
    pList[STATE_UNEXPLODED][2] = new RagParticle(pRadius[2], pDrag[2]);
    pList[STATE_UNEXPLODED][3] = new RagParticle(pRadius[3], pDrag[3]);
    pList[STATE_UNEXPLODED][4] = new RagParticle(pRadius[4], pDrag[4]);
    pList[STATE_UNEXPLODED][5] = new RagParticle(pRadius[5], pDrag[5]);

    pList[STATE_EXPLODED].resize(10);
    pList[STATE_EXPLODED][0] = new RagParticle(pRadius[0], pDrag[0]);
    pList[STATE_EXPLODED][1] = new RagParticle(pRadius[1], pDrag[1]);
    pList[STATE_EXPLODED][2] = new RagParticle(pRadius[2], pDrag[2]);
    pList[STATE_EXPLODED][3] = new RagParticle(pRadius[3], pDrag[3]);
    pList[STATE_EXPLODED][4] = new RagParticle(pRadius[4], pDrag[4]);
    pList[STATE_EXPLODED][5] = new RagParticle(pRadius[5], pDrag[5]);
    pList[STATE_EXPLODED][6] = new RagParticle(pRadius[0], pDrag[0]);
    pList[STATE_EXPLODED][7] = new RagParticle(pRadius[0], pDrag[0]);
    pList[STATE_EXPLODED][8] = new RagParticle(pRadius[1], pDrag[1]);
    pList[STATE_EXPLODED][9] = new RagParticle(pRadius[1], pDrag[1]);

    sList.resize(2);
    sList[STATE_UNEXPLODED].resize(5);
    sList[STATE_UNEXPLODED][0] = new RagStick(pList[STATE_UNEXPLODED][1], pList[STATE_UNEXPLODED][0], sWeight[0], sMinRatio[0], sMaxLen[0]);
    sList[STATE_UNEXPLODED][1] = new RagStick(pList[STATE_UNEXPLODED][0], pList[STATE_UNEXPLODED][2], sWeight[1], sMinRatio[1], sMaxLen[1]);
    sList[STATE_UNEXPLODED][2] = new RagStick(pList[STATE_UNEXPLODED][0], pList[STATE_UNEXPLODED][3], sWeight[2], sMinRatio[2], sMaxLen[2]);
    sList[STATE_UNEXPLODED][3] = new RagStick(pList[STATE_UNEXPLODED][1], pList[STATE_UNEXPLODED][4], sWeight[3], sMinRatio[3], sMaxLen[3]);
    sList[STATE_UNEXPLODED][4] = new RagStick(pList[STATE_UNEXPLODED][1], pList[STATE_UNEXPLODED][5], sWeight[4], sMinRatio[4], sMaxLen[4]);

    sList[STATE_EXPLODED].resize(5);
    sList[STATE_EXPLODED][0] = new RagStick(pList[STATE_EXPLODED][1], pList[STATE_EXPLODED][0], sWeight[0], sMinRatio[0], sMaxLen[0]);
    sList[STATE_EXPLODED][1] = new RagStick(pList[STATE_EXPLODED][6], pList[STATE_EXPLODED][2], sWeight[1], sMinRatio[1], sMaxLen[1]);
    sList[STATE_EXPLODED][2] = new RagStick(pList[STATE_EXPLODED][7], pList[STATE_EXPLODED][3], sWeight[2], sMinRatio[2], sMaxLen[2]);
    sList[STATE_EXPLODED][3] = new RagStick(pList[STATE_EXPLODED][8], pList[STATE_EXPLODED][4], sWeight[3], sMinRatio[3], sMaxLen[3]);
    sList[STATE_EXPLODED][4] = new RagStick(pList[STATE_EXPLODED][9], pList[STATE_EXPLODED][5], sWeight[4], sMinRatio[4], sMaxLen[4]);
}

Ragdoll::~Ragdoll() {
    for (vector<RagParticle*>& pStates : pList) {
        for (RagParticle* particle : pStates) {
            delete particle;
        }
    }
    for (vector<RagStick*>& sStates : sList) {
        for (RagStick* stick : sStates) {
            delete stick;
        }
    }
}

void Ragdoll::ActivateRagdoll(const vec2& ninjaPos, const vec2& ninjaVel, const vec2& deathPos, const vec2& deathForce, const vector<vec2>& posePos, const vector<vec2>& poseVel) {
    const vector<vec2>* ragPartPos;
    const vector<vec2>* ragPartVel;

    cur_state = STATE_UNEXPLODED;
    explosion_accumulator = 0;

    if (!posePos.empty() && !poseVel.empty()) {
        ragPartPos = &posePos;
        ragPartVel = &poseVel;
    } else {
        ragPartPos = &debugpose_pos;
        ragPartVel = &debugpose_vel;
    }

    pList[STATE_UNEXPLODED][0]->SetState(ninjaPos.x + (*ragPartPos)[0].x, ninjaPos.y + (*ragPartPos)[0].y, ninjaVel.x + (*ragPartVel)[0].x, ninjaVel.y + (*ragPartVel)[0].y);
    pList[STATE_UNEXPLODED][1]->SetState(ninjaPos.x + (*ragPartPos)[1].x, ninjaPos.y + (*ragPartPos)[1].y, ninjaVel.x + (*ragPartVel)[1].x, ninjaVel.y + (*ragPartVel)[1].y);
    pList[STATE_UNEXPLODED][2]->SetState(ninjaPos.x + (*ragPartPos)[2].x, ninjaPos.y + (*ragPartPos)[2].y, ninjaVel.x + (*ragPartVel)[2].x, ninjaVel.y + (*ragPartVel)[2].y);
    pList[STATE_UNEXPLODED][3]->SetState(ninjaPos.x + (*ragPartPos)[3].x, ninjaPos.y + (*ragPartPos)[3].y, ninjaVel.x + (*ragPartVel)[3].x, ninjaVel.y + (*ragPartVel)[3].y);
    pList[STATE_UNEXPLODED][4]->SetState(ninjaPos.x + (*ragPartPos)[4].x, ninjaPos.y + (*ragPartPos)[4].y, ninjaVel.x + (*ragPartVel)[4].x, ninjaVel.y + (*ragPartVel)[4].y);
    pList[STATE_UNEXPLODED][5]->SetState(ninjaPos.x + (*ragPartPos)[5].x, ninjaPos.y + (*ragPartPos)[5].y, ninjaVel.x + (*ragPartVel)[5].x, ninjaVel.y + (*ragPartVel)[5].y);

    ShoveRagdoll(deathPos, deathForce);
}

void Ragdoll::ShoveRagdoll(const vec2& impactPos, const vec2& impactForce) {
    double maxDist = 12.0;
    double minMultiplier = 0.5;
    double maxMultiplier = 1.5;

    for (int i = 0; i < pList[STATE_UNEXPLODED].size(); ++i) {
        double distX = pList[STATE_UNEXPLODED][i]->pos.x - impactPos.x;
        double distY = pList[STATE_UNEXPLODED][i]->pos.y - impactPos.y;
        double distance = sqrt(distX * distX + distY * distY);
        double ratio = min(1.0, distance / maxDist);
        double multiplier = minMultiplier + (1.0 - ratio) * maxMultiplier;
        pList[STATE_UNEXPLODED][i]->vel.x += impactForce.x * multiplier;
        pList[STATE_UNEXPLODED][i]->vel.y += impactForce.y * multiplier;
    }
}

void Ragdoll::ShoveParticle() { }

bool Ragdoll::DEBUG_IsExploded() {
    return cur_state == STATE_EXPLODED;
}

void Ragdoll::ExplodeRagdoll(Simulator* sim) {
    if (cur_state != STATE_EXPLODED) {
        cur_state = STATE_EXPLODED;
        InitUnexplodedParticles();
        for (int i = 6; i < 10; ++i) {
            //sim->HACKY_GetParticleManager()->Spawn_BloodSpurt(pList[STATE_EXPLODED][i]->pos.x, pList[STATE_EXPLODED][i]->pos.y, mathutils::Random() * 8 - 4, mathutils::Random() * 8 - 4, 3);
        }
    }
}

void Ragdoll::UnexplodeRagdoll() {
    if (cur_state != STATE_UNEXPLODED) {
        cur_state = STATE_UNEXPLODED;
        for (int i = 0; i < 6; ++i) {
            pList[STATE_UNEXPLODED][i]->CopyState(pList[STATE_EXPLODED][i]);
        }
    }
}

void Ragdoll::InitUnexplodedParticles() {
    pList[STATE_EXPLODED][0]->CopyState(pList[STATE_UNEXPLODED][0]);
    pList[STATE_EXPLODED][1]->CopyState(pList[STATE_UNEXPLODED][1]);
    pList[STATE_EXPLODED][2]->CopyState(pList[STATE_UNEXPLODED][2]);
    pList[STATE_EXPLODED][3]->CopyState(pList[STATE_UNEXPLODED][3]);
    pList[STATE_EXPLODED][4]->CopyState(pList[STATE_UNEXPLODED][4]);
    pList[STATE_EXPLODED][5]->CopyState(pList[STATE_UNEXPLODED][5]);
    pList[STATE_EXPLODED][6]->CopyState(pList[STATE_UNEXPLODED][0]);
    pList[STATE_EXPLODED][7]->CopyState(pList[STATE_UNEXPLODED][0]);
    pList[STATE_EXPLODED][8]->CopyState(pList[STATE_UNEXPLODED][1]);
    pList[STATE_EXPLODED][9]->CopyState(pList[STATE_UNEXPLODED][1]);
    pList[STATE_EXPLODED][6]->vel.x += 2;
    pList[STATE_EXPLODED][7]->vel.y += 4;
    pList[STATE_EXPLODED][8]->vel.y -= 6;
    pList[STATE_EXPLODED][9]->vel.x -= 8;
}

void Ragdoll::Integrate(double g) {
    for (int i = 0; i < pList[cur_state].size(); i++) {
        pList[cur_state][i]->PreIntegrate(g);
    }
}

void Ragdoll::PreCollision() { }

void Ragdoll::SolveConstraints() {
    for (int i = 0; i < sList[cur_state].size(); i++) {
        sList[cur_state][i]->Solve();
    }
}

void Ragdoll::PostCollision(Simulator* sim) {
    for (int i = 0; i < pList[cur_state].size(); ++i) {
        pList[cur_state][i]->PostIntegrate();
    }

    const double epsilon = 0.1;
    result_logical.Clear();

    for (int i = 0; i < pList[cur_state].size(); ++i) {
        RagParticle* part = pList[cur_state][i];
        sim->objGrid->GatherCellContentsInNeighbourhood(part->pos, objList);

        for (int j = 0; j < objList.size(); ++j) {
            Entity_Base* entity = objList[j];
            if (entity->CollideVsCircle_Logical(sim, nullptr, result_logical, part->pos, part->vel, part->pos, part->r, epsilon)) {
                part->vel.x += result_logical.vec_x;
                part->vel.y += result_logical.vec_y;

                if (dynamic_cast<Entity_Mine*>(entity)) {
                    if (cur_state == STATE_UNEXPLODED) {
                        explosion_accumulator += mathutils::Random() * 0.6;
                        if (mathutils::Random() < explosion_accumulator) {
                            ExplodeRagdoll(sim);
                        }
                    }
                } else if (dynamic_cast<Entity_Drone_Zap*>(entity) || dynamic_cast<Entity_FloorGuard*>(entity) || dynamic_cast<Entity_Thwomp*>(entity)) {
                    if (mathutils::Random() < 0.5) {
                        //sim->HACKY_GetSoundManager()->PlaySound_Ragdoll("zap1");
                    } else {
                        //sim->HACKY_GetSoundManager()->PlaySound_Ragdoll("zap2");
                    }
                }
            }
        }
    }
}

void Ragdoll::CollideVsObjects(Simulator* sim) {
    result_physical.Clear();

    for (int i = 0; i < pList[cur_state].size(); ++i) {
        RagParticle* part = pList[cur_state][i];
        sim->objGrid->GatherCellContentsInNeighbourhood(part->solver_pos, objList);
        for (int j = 0; j < objList.size(); ++j) {
            Entity_Base* entity = objList[j];
            if (entity->CollideVsCircle_Physical(result_physical, part->solver_pos, part->vel, part->pos, part->r)) {
                RespondToCollision(sim, part, result_physical.nx, result_physical.ny, result_physical.pen);
            }
        }
    }
}

void Ragdoll::CollideVsTiles(Simulator* sim) {
    for (int i = 0; i < pList[cur_state].size(); ++i) {
        RagParticle* part = pList[cur_state][i];
        int maxIterations = 32;
        cp.x = 0;
        cp.y = 0;

        for (int j = 0; j < maxIterations; ++j) {
            int cpSign = colutils::GetSingleClosestPoint_Signed(sim->segGrid, part->solver_pos, part->r * 4, cp);
            if (cpSign == 0) break;
            
            double dx = part->solver_pos.x - cp.x;
            double dy = part->solver_pos.y - cp.y;
            double dist = sqrt(dx * dx + dy * dy);
            double pen = part->r - cpSign * dist;

            if (pen < 1e-7) break;
            if (dist == 0) return;

            dx /= dist;
            dy /= dist;
            RespondToCollision(sim, dist, dx, dy, cpSign * pen);
        }
    }
}

void Ragdoll::GFX_UpdateState(EntityGraphics_Ninja* graphic) {

}

void Ragdoll::TESTING_SetPosVel(const vec2& partPos, const vec2& partVel) {
    pList[cur_state][0]->pos.Copy(partPos);
    pList[cur_state][0]->vel.Copy(partVel);
}

void Ragdoll::Draw(SimpleRenderer& rend) {
    //rend.SetStyle(0, 0, 100);

    for (int i = 0; i < pList[cur_state].size(); ++i){
        RagParticle* particle = pList[cur_state][i];
        //rend.DrawCircle(particle->pos.x, particle->pos.y, particle->r);
    }

    for (int i = 0; i < sList[cur_state].size(); ++i) {
        RagStick* stick = sList[cur_state][i];
        vec2 p0pos = stick->p0->pos;
        vec2 p1pos = stick->p1->pos;
        //rend.DrawLine(p0pos.x, p0pos.y, p1pos.x, p1pos.y);
    }
}

RagParticle::RagParticle(double radius, double drag)
    : r(radius), d(drag) { }

void RagParticle::PreIntegrate(double g) {
    vel.x *= d;
    vel.y *= d;
    vel.y += g;
    solver_pos.x = pos.x + vel.x;
    solver_pos.y = pos.y + vel.y;
}

void RagParticle::PostIntegrate() {
    vel.x = solver_pos.x - pos.x;
    vel.y = solver_pos.y - pos.y;
    pos.x = solver_pos.x;
    pos.y = solver_pos.y;
}

void RagParticle::SetState(double posx, double posy, double velx, double vely) {
    pos.x = posx;
    pos.y = posy;
    vel.x = velx;
    vel.y = vely;
}

void RagParticle::CopyState(const RagParticle* part) {
    pos.Copy(part->pos);
    vel.Copy(part->vel);
}

RagStick::RagStick(RagParticle* part0, RagParticle* part1, double weight0, double minRatio, double maxLength)
    : p0(part0), p1(part1), w0(weight0), w1(1 - weight0), minlen(maxLength * minRatio), maxlen(maxLength) { }

void RagStick::Solve() {
    double dx = p1->solver_pos.x - p0->solver_pos.x;
    double dy = p1->solver_pos.y - p0->solver_pos.y;
    double dist = sqrt(dx * dx + dy * dy);

    if (minlen <= dist && dist <= maxlen) {
        return;
    }

    double targetLength = max(minlen, min(maxlen, dist));
    double diff = dist - targetLength;
    double normX = 1;
    double normY = 0;

    if (dist != 0) {
        normX = dx / dist;
        normY = dy / dist;
    }

    p0->solver_pos.x -= w0 * -diff * normX;
    p0->solver_pos.y -= w0 * -diff * normY;
    p1->solver_pos.x += w1 * -diff * normX;
    p1->solver_pos.y += w1 * -diff * normY;
}