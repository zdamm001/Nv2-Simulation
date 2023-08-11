#pragma once
#include <vector>

#include "..\\math\\vec2.h"

using namespace std;

class edat {
    public:
        static const int num_cols = 31;
        static const int num_rows = 23;
        static const int cell_size = 24;
        static const int quantize_steps_per_cell = 4;
        static const int quantize_step_size = 6;

        static const unsigned int ETYPE_PLAYER = 0;
        static const unsigned int ETYPE_MINE = 1;
        static const unsigned int ETYPE_GOLD = 2;
        static const unsigned int ETYPE_DOOR_REGULAR = 3;
        static const unsigned int ETYPE_DOOR_LOCKED = 4;
        static const unsigned int ETYPE_SWITCH_LOCKED = 5;
        static const unsigned int ETYPE_DOOR_TRAP = 6;
        static const unsigned int ETYPE_SWITCH_TRAP = 7;
        static const unsigned int ETYPE_ONEWAY = 8;
        static const unsigned int ETYPE_EXIT_DOOR = 9;
        static const unsigned int ETYPE_EXIT_SWITCH = 10;
        static const unsigned int ETYPE_CHAINGUN = 11;
        static const unsigned int ETYPE_LASER = 12;
        static const unsigned int ETYPE_ZAP = 13;
        static const unsigned int ETYPE_CHASER = 14;
        static const unsigned int ETYPE_FLOORGUARD = 15;
        static const unsigned int ETYPE_LAUNCHPAD = 16;
        static const unsigned int ETYPE_BOUNCEBLOCK = 17;
        static const unsigned int ETYPE_ROCKET = 18;
        static const unsigned int ETYPE_TURRET = 19;
        static const unsigned int ETYPE_THWOMP = 20;
        static const unsigned int num_etypes = 21;

        static const unsigned int ETYPE_NULLFLAG = 999;
        static const unsigned int EPROP_TYPE = 0;
        static const unsigned int EPROP_X = 1;
        static const unsigned int EPROP_Y = 2;
        static const unsigned int EPROP_DIR = 3;
        static const unsigned int EPROP_MOVE = 4;

        static const unsigned int DIR_R = 0;
        static const unsigned int DIR_RD = 1;
        static const unsigned int DIR_D = 2;
        static const unsigned int DIR_LD = 3;
        static const unsigned int DIR_L = 4;
        static const unsigned int DIR_LU = 5;
        static const unsigned int DIR_U = 6;
        static const unsigned int DIR_RU = 7;

        static const unsigned int MOVE_SURFACE_CW = 0;
        static const unsigned int MOVE_SURFACE_CCW = 1;
        static const unsigned int MOVE_WANDER_CW = 2;
        static const unsigned int MOVE_WANDER_CCW = 3;

        static vector<unsigned int> HELPER_MIRROR_MOVE;
        static vector<unsigned int> MAP_TILETYPE_TO_TILEID;
        //static vector<Class> MAP_ETYPE_TO_MC;
        //static vector<Class> MAP_ETYPE_TO_MC_SELECTED;
        static vector<vec2> HELPER_MAP_DIR_TO_VEC;
        static vector<vec2> HELPER_MAP_ETYPE_TO_COLSHAPE;

        static const unsigned int STRUCTTYPE_PLAYER = 0;
        static const unsigned int STRUCTTYPE_MINE = 1;
        static const unsigned int STRUCTTYPE_GOLD = 2;
        static const unsigned int STRUCTTYPE_EXIT = 3;
        static const unsigned int STRUCTTYPE_DOOR_REGULAR = 4;
        static const unsigned int STRUCTTYPE_DOOR_LOCKED = 5;
        static const unsigned int STRUCTTYPE_DOOR_TRAP = 6;
        static const unsigned int STRUCTTYPE_LAUNCHPAD = 7;
        static const unsigned int STRUCTTYPE_ONEWAY = 8;
        static const unsigned int STRUCTTYPE_CHAINGUN = 9;
        static const unsigned int STRUCTTYPE_LASER = 10;
        static const unsigned int STRUCTTYPE_ZAP = 11;
        static const unsigned int STRUCTTYPE_CHASER = 12;
        static const unsigned int STRUCTTYPE_FLOORGUARD = 13;
        static const unsigned int STRUCTTYPE_BOUNCEBLOCK = 14;
        static const unsigned int STRUCTTYPE_ROCKET = 15;
        static const unsigned int STRUCTTYPE_TURRET = 16;
        static const unsigned int STRUCTTYPE_THWOMP = 17;
        static const unsigned int num_structtypes = 18;

        static vector<unsigned int> STRUCT_SIZE;
        static vector<unsigned int> MAP_STRUCT_TO_ETYPE;
    public:
        edat() = delete;
        static void Initialize();
        static vec2 GET_WORLDSPACE_POS(const vector<unsigned int>& data);
        static vec2 MAP_DIR_TO_VEC(int direction);
        static vec2 GET_COLLISION_SHAPE(const vector<unsigned int>& data);
};