#pragma once
#include <string>

#include "Level.h"

using namespace std;

class Options {
    public:
        string enteredTerm = "";
        string enteredType;
        string selectedTerm;
        string selectedType;
        double volume = 1.0;
        bool coopMode;
        Level selectedLevel;
        int selectedLevelIndexInSearch = -1;
        int selectedEpisode = -1;
        int selectedChallenge = -1;
        int ticksToResumeWith;
        bool scoreGoldImmediately;
        bool resetScoreOnDeath;
        int ninjaFlavour;
        unsigned int p1Colour;
        unsigned int p2Colour;
    public:
        Options() {};
};
