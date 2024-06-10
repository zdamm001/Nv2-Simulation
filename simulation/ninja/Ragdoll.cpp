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
    pList[STATE_UNEXPLODED][0] = RagParticle(pRadius[0], pDrag[0]);
    pList[STATE_UNEXPLODED][1] = RagParticle(pRadius[1], pDrag[1]);
    pList[STATE_UNEXPLODED][2] = RagParticle(pRadius[2], pDrag[2]);
    pList[STATE_UNEXPLODED][3] = RagParticle(pRadius[3], pDrag[3]);
    pList[STATE_UNEXPLODED][4] = RagParticle(pRadius[4], pDrag[4]);
    pList[STATE_UNEXPLODED][5] = RagParticle(pRadius[5], pDrag[5]);

    pList[STATE_EXPLODED].resize(10);
    pList[STATE_EXPLODED][0] = RagParticle(pRadius[0], pDrag[0]);
    pList[STATE_EXPLODED][1] = RagParticle(pRadius[1], pDrag[1]);
    pList[STATE_EXPLODED][2] = RagParticle(pRadius[2], pDrag[2]);
    pList[STATE_EXPLODED][3] = RagParticle(pRadius[3], pDrag[3]);
    pList[STATE_EXPLODED][4] = RagParticle(pRadius[4], pDrag[4]);
    pList[STATE_EXPLODED][5] = RagParticle(pRadius[5], pDrag[5]);
    pList[STATE_EXPLODED][6] = RagParticle(pRadius[0], pDrag[0]);
    pList[STATE_EXPLODED][7] = RagParticle(pRadius[0], pDrag[0]);
    pList[STATE_EXPLODED][8] = RagParticle(pRadius[1], pDrag[1]);
    pList[STATE_EXPLODED][9] = RagParticle(pRadius[1], pDrag[1]);

    sList.resize(2);
    sList[STATE_UNEXPLODED].resize(5);
    sList[STATE_UNEXPLODED][0] = RagStick(pList[STATE_UNEXPLODED][1], pList[STATE_UNEXPLODED][0], sWeight[0], sMinRatio[0], sMaxLen[0]);
    sList[STATE_UNEXPLODED][1] = RagStick(pList[STATE_UNEXPLODED][0], pList[STATE_UNEXPLODED][2], sWeight[1], sMinRatio[1], sMaxLen[1]);
    sList[STATE_UNEXPLODED][2] = RagStick(pList[STATE_UNEXPLODED][0], pList[STATE_UNEXPLODED][3], sWeight[2], sMinRatio[2], sMaxLen[2]);
    sList[STATE_UNEXPLODED][3] = RagStick(pList[STATE_UNEXPLODED][1], pList[STATE_UNEXPLODED][4], sWeight[3], sMinRatio[3], sMaxLen[3]);
    sList[STATE_UNEXPLODED][4] = RagStick(pList[STATE_UNEXPLODED][1], pList[STATE_UNEXPLODED][5], sWeight[4], sMinRatio[4], sMaxLen[4]);

    sList[STATE_EXPLODED].resize(5);
    sList[STATE_EXPLODED][0] = RagStick(pList[STATE_EXPLODED][1], pList[STATE_EXPLODED][0], sWeight[0], sMinRatio[0], sMaxLen[0]);
    sList[STATE_EXPLODED][1] = RagStick(pList[STATE_EXPLODED][6], pList[STATE_EXPLODED][2], sWeight[1], sMinRatio[1], sMaxLen[1]);
    sList[STATE_EXPLODED][2] = RagStick(pList[STATE_EXPLODED][7], pList[STATE_EXPLODED][3], sWeight[2], sMinRatio[2], sMaxLen[2]);
    sList[STATE_EXPLODED][3] = RagStick(pList[STATE_EXPLODED][8], pList[STATE_EXPLODED][4], sWeight[3], sMinRatio[3], sMaxLen[3]);
    sList[STATE_EXPLODED][4] = RagStick(pList[STATE_EXPLODED][9], pList[STATE_EXPLODED][5], sWeight[4], sMinRatio[4], sMaxLen[4]);
}

void Ragdoll::GFX_UpdateState(EntityGraphics_Ninja* graphic) {

}

RagParticle::RagParticle(double param1, double drag)
    : r(param1), d(drag) { }

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

void RagParticle::CopyState(const RagParticle &part) {
    pos.Copy(part.pos);
    vel.Copy(part.vel);
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