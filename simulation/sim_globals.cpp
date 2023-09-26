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

vector<string> sim_globals::ETYPE_TO_STRING(13);
vector<int> sim_globals::ETYPE_TO_DTYPE(13);
bool sim_globals::HORRIBLY_HACKY_DOES_STRING_TO_BA_ERROR_EXIST = false;

void sim_globals::Initialize() {
    ETYPE_TO_STRING[ENEMYTYPE_SUICIDE] = "suicide";
    ETYPE_TO_STRING[ENEMYTYPE_FALL] = "falling";
    ETYPE_TO_STRING[ENEMYTYPE_CRUSH] = "crushed";
    ETYPE_TO_STRING[ENEMYTYPE_TIME] = "out of time";
    ETYPE_TO_STRING[ENEMYTYPE_ZAP] = "zap";
    ETYPE_TO_STRING[ENEMYTYPE_CHAINGUN] = "chaingun";
    ETYPE_TO_STRING[ENEMYTYPE_LASER] = "laser";
    ETYPE_TO_STRING[ENEMYTYPE_TURRET] = "turret";
    ETYPE_TO_STRING[ENEMYTYPE_ROCKET] = "rocket";
    ETYPE_TO_STRING[ENEMYTYPE_FLOORGUARD] = "floorguard";
    ETYPE_TO_STRING[ENEMYTYPE_THWOMP] = "thwomp";
    ETYPE_TO_STRING[ENEMYTYPE_MINE] = "mine";
    ETYPE_TO_STRING[ENEMYTYPE_DEBUG] = "debug";
    ETYPE_TO_DTYPE[ENEMYTYPE_SUICIDE] = DEATHTYPE_EXPLOSIVE;
    ETYPE_TO_DTYPE[ENEMYTYPE_FALL] = DEATHTYPE_FALL;
    ETYPE_TO_DTYPE[ENEMYTYPE_CRUSH] = DEATHTYPE_CRUSH;
    ETYPE_TO_DTYPE[ENEMYTYPE_TIME] = DEATHTYPE_EXPLOSIVE;
    ETYPE_TO_DTYPE[ENEMYTYPE_ROCKET] = DEATHTYPE_EXPLOSIVE;
    ETYPE_TO_DTYPE[ENEMYTYPE_MINE] = DEATHTYPE_EXPLOSIVE;
    ETYPE_TO_DTYPE[ENEMYTYPE_LASER] = DEATHTYPE_LASER;
    ETYPE_TO_DTYPE[ENEMYTYPE_ZAP] = DEATHTYPE_ELECTRIC;
    ETYPE_TO_DTYPE[ENEMYTYPE_FLOORGUARD] = DEATHTYPE_ELECTRIC;
    ETYPE_TO_DTYPE[ENEMYTYPE_THWOMP] = DEATHTYPE_ELECTRIC;
    ETYPE_TO_DTYPE[ENEMYTYPE_CHAINGUN] = DEATHTYPE_BULLET;
    ETYPE_TO_DTYPE[ENEMYTYPE_TURRET] = DEATHTYPE_BULLET;
    ETYPE_TO_DTYPE[ENEMYTYPE_DEBUG] = DEATHTYPE_BULLET;
}

string sim_globals::BAtoString(ByteArray& bytes) {
    if (bytes.length() == 0) {
        return ""; //bytes == null
    }
    string hexString = "";
    bytes.setPosition(0);
    while(bytes.bytesAvailable()) {
        unsigned int byteValue = bytes.readByte();
        hexString += "0123456789abcdef"[byteValue % 16];
        byteValue >>= 4;
        hexString += "0123456789abcdef"[byteValue % 16];
    }
    bytes.setPosition(0);
    return hexString;
}

ByteArray sim_globals::StringtoBA(string hexString) {
    HORRIBLY_HACKY_DOES_STRING_TO_BA_ERROR_EXIST = false;
    ByteArray bytes;
    for (int i = 0; i < hexString.size(); i += 2) {
        unsigned int byteValue = BAS_hint(hexString[i]) + (BAS_hint(hexString[i + 1]) << 4);
        bytes.writeByte(byteValue);
    }
    bytes.setPosition(0);
    return bytes;
}

unsigned int sim_globals::BAS_hint(char hexChar) {
    switch (hexChar) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'a':
            return 10;
        case 'b':
            return 11;
        case 'c':
            return 12;
        case 'd':
            return 13;
        case 'e':
            return 14;
        case 'f':
            return 15;
        default:
            HORRIBLY_HACKY_DOES_STRING_TO_BA_ERROR_EXIST = true;
            return 16;
    }
}