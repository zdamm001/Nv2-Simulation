#pragma once

#include <vector>
#include <string>

using namespace std;

class sim_globals {
    public:
        static double sim_rate;
        static const int DEATHTYPE_SUICIDE;
        static const int DEATHTYPE_FALL;
        static const int DEATHTYPE_CRUSH;
        static const int DEATHTYPE_TIME;
        static const int DEATHTYPE_EXPLOSIVE;
        static const int DEATHTYPE_LASER;
        static const int DEATHTYPE_ELECTRIC;
        static const int DEATHTYPE_BULLET;
        static const int ENEMYTYPE_SUICIDE;
        static const int ENEMYTYPE_FALL;
        static const int ENEMYTYPE_CRUSH;
        static const int ENEMYTYPE_TIME;
        static const int ENEMYTYPE_ZAP;
        static const int ENEMYTYPE_CHAINGUN;
        static const int ENEMYTYPE_LASER;
        static const int ENEMYTYPE_TURRET;
        static const int ENEMYTYPE_ROCKET;
        static const int ENEMYTYPE_FLOORGUARD;
        static const int ENEMYTYPE_THWOMP;
        static const int ENEMYTYPE_MINE;
        static const int ENEMYTYPE_DEBUG;
        static const vector<string> ETYPE_TO_STRING;
        static const vector<int> ETYPE_TO_DTYPE;
        static bool HORRIBLY_HACKY_DOES_STRING_TO_BA_ERROR_EXIST;
    public:
        sim_globals() = delete;
};

double sim_globals::sim_rate = 40;

const int sim_globals::DEATHTYPE_SUICIDE = 0;
const int sim_globals::DEATHTYPE_FALL = 1;
const int sim_globals::DEATHTYPE_CRUSH = 2;
const int sim_globals::DEATHTYPE_TIME = 3;
const int sim_globals::DEATHTYPE_EXPLOSIVE = 4;
const int sim_globals::DEATHTYPE_LASER = 5;
const int sim_globals::DEATHTYPE_ELECTRIC = 6;
const int sim_globals::DEATHTYPE_BULLET = 7;

const int sim_globals::ENEMYTYPE_SUICIDE = 0;
const int sim_globals::ENEMYTYPE_FALL = 1;
const int sim_globals::ENEMYTYPE_CRUSH = 2;
const int sim_globals::ENEMYTYPE_TIME = 3;
const int sim_globals::ENEMYTYPE_ZAP = 4;
const int sim_globals::ENEMYTYPE_CHAINGUN = 5;
const int sim_globals::ENEMYTYPE_LASER = 6;
const int sim_globals::ENEMYTYPE_TURRET = 7;
const int sim_globals::ENEMYTYPE_ROCKET = 8;
const int sim_globals::ENEMYTYPE_FLOORGUARD = 9;
const int sim_globals::ENEMYTYPE_THWOMP = 10;
const int sim_globals::ENEMYTYPE_MINE = 11;
const int sim_globals::ENEMYTYPE_DEBUG = 12;

const vector<string> sim_globals::ETYPE_TO_STRING = {
    "suicide", 
    "falling", 
    "crushed", 
    "out of time", 
    "zap", 
    "chaingun", 
    "laser",
    "turret", 
    "rocket", 
    "floorguard", 
    "thwomp", 
    "mine", 
    "debug"
};

const vector<int> sim_globals::ETYPE_TO_DTYPE = {
    DEATHTYPE_EXPLOSIVE, 
    DEATHTYPE_FALL, 
    DEATHTYPE_CRUSH, 
    DEATHTYPE_EXPLOSIVE,
    DEATHTYPE_EXPLOSIVE, 
    DEATHTYPE_EXPLOSIVE, 
    DEATHTYPE_LASER, 
    DEATHTYPE_ELECTRIC,
    DEATHTYPE_ELECTRIC, 
    DEATHTYPE_ELECTRIC, 
    DEATHTYPE_BULLET, 
    DEATHTYPE_BULLET, 
    DEATHTYPE_BULLET
};

bool sim_globals::HORRIBLY_HACKY_DOES_STRING_TO_BA_ERROR_EXIST = false;