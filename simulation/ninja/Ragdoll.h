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
        vector<vector<RagParticle*>> pList;
        vector<vector<RagStick*>> sList;
        vector<Entity_Base*> objList;
        collision_result_logical result_logical;
        collision_result_physical result_physical;
        vec2 cp;
    public:
        Ragdoll();
        ~Ragdoll();
        void ActivateRagdoll(const vec2& ninjaPos, const vec2& ninjaVel, const vec2& deathPos, const vec2& deathForce, const vector<vec2>& posePos, const vector<vec2>& poseVel);
    private:
        void ShoveRagdoll(const vec2& impactPos, const vec2& impactForce);
        void ShoveParticle();
    public:
        bool DEBUG_IsExploded();
        void ExplodeRagdoll(Simulator* sim);
        void UnexplodeRagdoll();
    private:
        void InitUnexplodedParticles();
    public:
        void Integrate(double g);
        void PreCollision();
        void SolveConstraints();
        void PostCollision(Simulator* sim);
        void CollideVsObjects(Simulator* sim);
        void CollideVsTiles(Simulator* sim);
    private:
        void RespondToCollision(Simulator* sim, RagParticle* part, double normx, double normy, double pen);
    public:
        void GFX_UpdateState(EntityGraphics_Ninja* graphic);
        void TESTING_SetPosVel(const vec2& partPos, const vec2& partVel);
        void Draw(SimpleRenderer& rend);
};

class RagParticle {
    public:
        vec2 pos;
        vec2 vel;
        vec2 solver_pos;
        double r;
        double d;
    public:
        RagParticle(double radius, double drag);
        void PreIntegrate(double g);
        void PostIntegrate();
        void SetState(double posx, double posy, double velx, double vely);
        void CopyState(const RagParticle* part);
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