#pragma once
#include <cmath>
#include <string>
#include <vector>

#include "..\\..\\math\vec2.h"
#include "..\\entities\\Entity_Base.h"
#include "..\\entities\\collision_result_logical.h"
#include "..\\entities\\collision_result_physical.h"
#include "..\\sim_globals.h"

using namespace std;

class InputSource_Base;
class Ragdoll {};
class EntityGraphics_Ninja {public: EntityGraphics_Ninja(EntityGraphics_Ninja*);};
class Segment;

class Ninja {
    public:
        static const unsigned int PSTATE_STANDING;
        static const unsigned int PSTATE_RUNNING;
        static const unsigned int PSTATE_SKIDDING;
        static const unsigned int PSTATE_JUMPING;
        static const unsigned int PSTATE_FALLING;
        static const unsigned int PSTATE_WALLSLIDING;
        static const unsigned int PSTATE_DEAD;
        static const unsigned int PSTATE_AWAITINGDEATH;
        static const unsigned int PSTATE_CELEBRATING;
        static const unsigned int PSTATE_DISABLED;
        static const vector<string> PSTATE_TO_STRING;
        InputSource_Base* inputsource;
    private:
        vec2 pos;
        vec2 vel;
        vec2 oldpos;
        double r;
        double g;
        double d;
        double maxspeedAir;
        double maxspeedGround;
        double groundAccel;
        double airAccel;
        double normGrav;
        double jumpGrav;
        double normDrag;
        double winDrag;
        double wallFriction;
        double skidFriction;
        double standFriction;
        unsigned int curState;
        int facingDir;
        double max_jump_time;
        double jumptimer;
        double jumpAmt;
        double jump_y_bias;
        double terminal_vel;
        bool wasJdown;
        vec2 oldv;
        bool WAS_IN_AIR;
        bool IN_AIR;
        bool NEAR_WALL;
        vec2 wallN;
        vec2 floorN;
        int fcount;
        vec2 fvec;
        double impulse_scale;
        int pID;
        Ragdoll raggy;
        EntityGraphics_Ninja ninja_gfx;
        double crush_threshold;
        vec2 crush_vec;
        double crush_dist;
        bool crush_flag;
        int death_type;
        vec2 death_pos;
        vec2 death_force;
        vec2 TEMP_near_pos;
        vector<Entity_Base*> objList;
        vector<Segment> segList;
        vec2 seg_cp;
        vector<double> wallList_X;
        vector<double> wallList_Y;
        collision_result_logical result_logical;
        collision_result_physical result_physical;
        vec2 cp;
        vec2 tempV;
        vec2 tempP;
        vec2 public_pos;
        vec2 public_vel;
        unsigned int gfxColor;
    public:
        Ninja(int param1, InputSource_Base* param2, double param3, double param4, unsigned int param5);
        void Integrate();
        void PreCollision();
        void SolveInternalConstraints();
        void PostCollision(Simulator* sim);
        void RespondToCollision(double param1, double param2, double param3, bool param4, bool param5);
        void CollideVsObjects(Simulator* sim);
        void CollideVsTiles(Simulator* sim);
        void Think(Simulator* sim, unsigned int frame_num);
};