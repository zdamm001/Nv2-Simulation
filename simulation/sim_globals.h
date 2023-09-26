#pragma once
#include <vector>
#include <string>

#include "..\\flash\\utils\\ByteArray.h"

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
        static vector<string> ETYPE_TO_STRING;
        static vector<int> ETYPE_TO_DTYPE;
        static bool HORRIBLY_HACKY_DOES_STRING_TO_BA_ERROR_EXIST;
    public:
        sim_globals() = delete;
        static void Initialize();
        static string BAtoString(ByteArray& bytes);
        static ByteArray StringtoBA(string hexString);
        static unsigned int BAS_hint(char hexChar);
};