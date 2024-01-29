#include "TimeFormatter.h"

TimeFormatter::TimeFormatter() {}

string TimeFormatter::formatTime(int ticks, int sim_rate) {
    double seconds = static_cast<double>(ticks) / sim_rate;
    istringstream ssin(to_string(seconds));
    vector<string> secondParts;

    string part;
    while (getline(ssin, part, '.')) {
        secondParts.push_back(part);
    }

    string wholeSeconds = secondParts[0];
    string fractionalSeconds;

    if (secondParts.size() == 1) {
        fractionalSeconds = "000";
    } else {
        fractionalSeconds = secondParts[1].substr(0, 3);
    }

    while (wholeSeconds.length() < 4) {
        wholeSeconds = " " + wholeSeconds;
    }

    while (fractionalSeconds.length() < 3) {
        fractionalSeconds += "0";
    }

    return wholeSeconds + fractionalSeconds;
}