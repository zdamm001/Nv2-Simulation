#pragma once
#include <vector>
#include <cmath>

#include "..\\..\\audiovisual\\entitygraphics\\EntityGraphics_Ninja.h"
#include "..\\..\\math\\mathutils.h"
#include "..\\..\\math\\vec2.h"
#include "..\\..\\simpleFramework\\SimpleRenderer.h"
#include "..\\Simulator.h"
#include "..\\collision\\colutils.h"
#include "..\\entities\\Entity_Base.h"
#include "..\\entities\\Entity_Drone_Zap.h"
#include "..\\entities\\Entity_FloorGuard.h"
#include "..\\entities\\Entity_Mine.h"
#include "..\\entities\\Entity_Thwomp.h"
#include "..\\entities\\collision_result_logical.h"
#include "..\\entities\\collision_result_physical.h"

class RagParticle;
class RagStick;

class Ragdoll {
    private:
        static const vector<double> pRadius;
        static const vector<double> pDrag;
        static const vector<double> sWeight;
        static const vector<double> sMinRatio;
        static constexpr double hacky_scale = 0.2;
        static const vector<double> sMaxLen;
        static const vector<vec2> debugpose_pos;
        static const vector<vec2> debugpose_vel;
        static constexpr int STATE_UNEXPLODED = 0;
        static constexpr int STATE_EXPLODED = 1;

        int cur_state;
        double explosion_accumulator = 0;
        vector<vector<RagParticle>> pList;
        vector<vector<RagStick>> sList;
        vector<Entity_Base*> objList;
        collision_result_logical result_logical;
        collision_result_physical result_physical;
        vec2 cp;
    public:
        Ragdoll();
        void GFX_UpdateState(EntityGraphics_Ninja* graphic);
};

class RagParticle {
    public:
        vec2 pos;
        vec2 vel;
        vec2 solver_pos;
        double r;
        double d;
    public:
        RagParticle(double param1, double drag);
        void PreIntegrate(double g);
        void PostIntegrate();
        void SetState(double posx, double posy, double velx, double vely);
        void CopyState(const RagParticle &part);
};

class RagStick {
    public:
        RagParticle* p0;
        RagParticle* p1;
        double w0;
        double w1;
        double minlen;
        double maxlen;
    public:
        RagStick(RagParticle* part0, RagParticle* part1, double weight0, double minRatio, double maxLength);
        void Solve();
};