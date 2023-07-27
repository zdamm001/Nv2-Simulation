#include "sim_globals.h"

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