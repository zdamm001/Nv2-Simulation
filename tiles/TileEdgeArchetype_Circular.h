#pragma once

#include "TileEdgeArchetype.h"
#include "..\\simulation\\collision\\Segment.h"
#include "..\\simulation\\collision\\Segment_Circular.h"

class TileEdgeArchetype_Circular : public TileEdgeArchetype {
    private:
        double x0;
        double y0;
        double x1;
        double y1;
        double x2;
        double y2;
    public:
        TileEdgeArchetype_Circular(double x0, double y0, double x1, double y1, double x2, double y2);
        TileEdgeArchetype* GeneratePerpArchetype() override;
        Segment* GenerateCollisionSegment(double xpos, double ypos, double halfWidth) override;
};