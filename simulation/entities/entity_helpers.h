#pragma once
#include <vector>

#include "..\\..\\math\\vec2.h"
#include "..\\collision\\Grid_Segment.h"
#include "..\\ninja\\Ninja.h"

class entity_helpers {
    public:
        static const vec2 zero_vec;
        static vector<int> potentialList;
    public:
        entity_helpers() = delete;
        static int TryToAquireTarget(const vec2& pos, const vector<Ninja*>& playerList, Grid_Segment& segGrid);
};
