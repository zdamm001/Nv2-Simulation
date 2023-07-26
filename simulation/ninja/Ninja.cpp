#pragma once
#include <string>
#include <vector>

#include "..\\entities\\collision_result_logical.cpp"
#include "..\\entities\\collision_result_physical.cpp"
#include "..\\sim_globals.cpp"

using namespace std;

class InputSource_Base;
class Ragdoll {};
class EntityGraphics_Ninja {};
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
        std::vector<Entity_Base*> objList;
        std::vector<Segment> segList;
        vec2 seg_cp;
        std::vector<double> wallList_X;
        std::vector<double> wallList_Y;
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
};

const unsigned int Ninja::PSTATE_STANDING = 0;
const unsigned int Ninja::PSTATE_RUNNING = 1;
const unsigned int Ninja::PSTATE_SKIDDING = 2;
const unsigned int Ninja::PSTATE_JUMPING = 3;
const unsigned int Ninja::PSTATE_FALLING = 4;
const unsigned int Ninja::PSTATE_WALLSLIDING = 5;
const unsigned int Ninja::PSTATE_DEAD = 6;
const unsigned int Ninja::PSTATE_AWAITINGDEATH = 7;
const unsigned int Ninja::PSTATE_CELEBRATING = 8;
const unsigned int Ninja::PSTATE_DISABLED = 9;

const std::vector<std::string> Ninja::PSTATE_TO_STRING = {
    "standing", 
    "running", 
    "skidding", 
    "jumping", 
    "falling",
    "wallsliding", 
    "dead", 
    "waiting to die", 
    "celebration", 
    "disabled"
};

Ninja::Ninja(int param1, InputSource_Base* param2, double param3, double param4, unsigned int param5)
    : pID(param1), 
      inputsource(param2), 
      gfxColor(param5), 
      pos(param3, param4), 
      vel(0, 0),
      oldpos(0, 0), 
      r(10), 
      impulse_scale(40.0 / sim_globals::sim_rate),
      maxspeedAir(r * 0.5 * (40.0 / sim_globals::sim_rate)),
      maxspeedGround(r * 0.5 * (40.0 / sim_globals::sim_rate)),
      groundAccel(0.15 * (40.0 / sim_globals::sim_rate) * (40.0 / sim_globals::sim_rate)),
      airAccel(0.1 * (40.0 / sim_globals::sim_rate) * (40.0 / sim_globals::sim_rate)),
      normGrav(0.15 * (40.0 / sim_globals::sim_rate) * (40.0 / sim_globals::sim_rate)),
      jumpGrav(0.025 * (40.0 / sim_globals::sim_rate) * (40.0 / sim_globals::sim_rate)),
      normDrag(std::pow(0.99, 40.0 / sim_globals::sim_rate)),
      winDrag(std::pow(0.8, 40.0 / sim_globals::sim_rate)),
      wallFriction(std::pow(0.87, 40.0 / sim_globals::sim_rate)),
      skidFriction(std::pow(0.92, 40.0 / sim_globals::sim_rate)),
      standFriction(std::pow(0.8, 40.0 / sim_globals::sim_rate)),
      g(normGrav), 
      d(normDrag), 
      curState(PSTATE_DISABLED), 
      facingDir(1), 
      jumpAmt(1),
      jump_y_bias(2), 
      max_jump_time(30 * (sim_globals::sim_rate / 40)),
      terminal_vel(r * 0.9 * (40.0 / sim_globals::sim_rate)), 
      jumptimer(0), 
      wasJdown(false),
      WAS_IN_AIR(false), 
      oldv(0, 0), 
      IN_AIR(false), 
      NEAR_WALL(false), 
      wallN(0, 0), 
      floorN(0, -1),
      fcount(1), 
      fvec(0, 0), 
      raggy(), 
      ninja_gfx(nullptr), 
      crush_threshold(0.05),
      crush_vec(), 
      crush_dist(0), 
      crush_flag(false), 
      death_type(sim_globals::DEATHTYPE_TIME),
      death_pos(), 
      death_force(), 
      TEMP_near_pos(), 
      objList(), 
      segList(), 
      seg_cp(), 
      wallList_X(),
      wallList_Y(), 
      result_logical(), 
      result_physical(), 
      cp(), 
      tempV(), 
      tempP(), 
      public_pos(),
      public_vel() { }
