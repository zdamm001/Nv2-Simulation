#pragma once
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class TimeFormatter {
    public:
        TimeFormatter();
        string formatTime(int ticks, int sim_rate);
};