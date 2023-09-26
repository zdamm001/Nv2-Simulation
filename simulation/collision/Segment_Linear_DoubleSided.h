#pragma once

#include "Segment_Linear.h"
#include "..\\..\\math\\vec2.h"
class SimpleRenderer;

class Segment_Linear_DoubleSided : public Segment_Linear {
    public:
        Segment_Linear_DoubleSided(double x0, double y0, double x1, double y1);
        bool GetClosestPoint_IsBackfacing(const vec2& query_pos, vec2& out_closestpoint) override;
        void DebugDraw_NoStyle(SimpleRenderer& rend) override;
};