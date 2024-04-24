#pragma once
#include <string>

#include "..\\..\\..\\flash\\utils\\ByteArray.h"

using namespace std;

class GameStats {
    public:
        bool isEpisode;
        string level;
        ByteArray* replayBytes;
        int score;
        string formattedTime;
    public:
        GameStats() {}
};