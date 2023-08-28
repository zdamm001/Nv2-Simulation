#pragma once
#include <string>

#include "..\\..\\..\\flash\\utils\\ByteArray.h"

using namespace std;

class Level {
    public:
        string id;
        string name = "Untitled";
        string creatorName;
        string creatorID;
        double meanRating;
        bool loaded;
        int personalBest;
        int minimumHighscore;
        bool favourite;
        ByteArray data;
        bool isNew = false;
        bool published;
        int personalRating;
        bool fullData = false;
        bool waitingForUpload;
    public:
        Level() {}
        bool isMetanetLevel() {return stoi(id) < 1000;}
};
