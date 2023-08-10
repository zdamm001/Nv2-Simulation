#pragma once

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
        edat() = delete;
};