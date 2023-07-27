#include "Ninja.h"

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

const vector<string> Ninja::PSTATE_TO_STRING = {
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
      normDrag(pow(0.99, 40.0 / sim_globals::sim_rate)),
      winDrag(pow(0.8, 40.0 / sim_globals::sim_rate)),
      wallFriction(pow(0.87, 40.0 / sim_globals::sim_rate)),
      skidFriction(pow(0.92, 40.0 / sim_globals::sim_rate)),
      standFriction(pow(0.8, 40.0 / sim_globals::sim_rate)),
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
