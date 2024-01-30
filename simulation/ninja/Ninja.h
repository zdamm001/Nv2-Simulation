#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <vector>

#include "..\\..\\audiovisual\\entitygraphics\\Entity_GraphicsNinja.h"
#include "..\\..\\math\vec2.h"
#include "..\\..\\simpleFramework\\SimpleRenderer.h"
#include "..\\collision\\Segment.h"
#include "..\\collision\\colutils.h"
#include "..\\entities\\Entity_Base.h"
#include "..\\entities\\Entity_Thwomp.h"
#include "..\\entities\\collision_result_logical.h"
#include "..\\entities\\collision_result_physical.h"
#include "..\\inputsource\\InputSource_Base.h"
#include "..\\sim_globals.h"
#include "Ragdoll.h"
#include "..\\save\\saveState.h"

using namespace std;

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
        static vector<string> PSTATE_TO_STRING;
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
        EntityGraphics_Ninja* ninja_gfx;
        double crush_threshold;
        vec2 crush_vec;
        double crush_dist;
        bool crush_flag;
        int death_type;
        vec2 death_pos;
        vec2 death_force;
        vec2 TEMP_near_pos;
        vector<Entity_Base*> objList;
        vector<Segment*> segList;
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
        //new for debugging
        unsigned int rcount;
        unsigned int lcount;
        unsigned int jcount;
    public:
        Ninja(int pID, InputSource_Base* input, double x, double y, unsigned int color);
        Ninja(ninjaSave& ninjaState, InputSource_Base* input);
        ~Ninja();
        static void Initialize();
        void DEBUG_SetPosVel(const vec2& pos, const vec2& vel);
        void DEBUG_Respawn(const vec2& pos);
        int GetIndex();
        vec2 GetPos();
        vec2 GetVel();
        double GetRadius();
        bool IsDead();
        Ragdoll& DEBUG_GetRagdoll();
        void APP_Enable();
        void APP_Disable();
        void Integrate();
        void PreCollision();
        void SolveInternalConstraints();
        void PostCollision(Simulator* sim);
        void RespondToCollision(double collisionNormalX, double collisionNormalY, double collisionPenetration, bool isHardCollision, bool isThwompCollision);
        void CollideVsObjects(Simulator* sim);
        void CollideVsTiles(Simulator* sim);
        void Think(Simulator* sim, unsigned int frame_num); //fix wrong variables here
    private:
        void ACTION_Jump(double jumpDirX, double jumpDirY);
        void ACTION_Fall();
        void ACTION_Wallslide();
        void ACTION_Skid();
        void ACTION_Run(double moveDirection);
        void ACTION_Stand();
        void ACTION_Die();
        void ACTION_Win();
        void HELPER_ExitCurrentState();
    public:
        void SIM_Launch(double launchForceX, double launchForceY);
        bool SIM_Kill(int enemyType, double deathPosX, double deathPosY, double deathForceX, double deathForceY);
        bool SIM_Win();
        EntityGraphics_Ninja* GenerateGraphicComponent();
        void GFX_UpdateState(EntityGraphics_Ninja* graphics);
        void Draw(SimpleRenderer& rend);
        unsigned int NEW_GetState() const;
        bool NEW_GetInAir() const;
        //ByteArray saveState();
        void saveState(ninjaSave& state);
};