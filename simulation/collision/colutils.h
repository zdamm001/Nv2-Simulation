#pragma once
#include <vector>

#include "..\\..\\math\\vec2.h"
#include "Grid_Segment.h"

using namespace std;

class Segment {};

class colutils {
    private:
        static vec2 closestPoint;
        static vector<Segment> segmentList;
    public:
        colutils() = delete;
        static int getSingleClosestPoint_Signed(Grid_Segment& gridSegment, vec2& point, double radius, vec2& closestPointResult);
        static double Penetration_Square_vs_Point(const vec2& squareCenter, double contactRadius, const vec2& pointPosition, vec2& penetrationNormal);
};