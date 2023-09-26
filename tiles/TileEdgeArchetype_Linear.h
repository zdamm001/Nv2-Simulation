#pragma once

#include "TileEdgeArchetype.h"
#include "..\\simulation\\collision\\Segment.h"
#include "..\\simulation\\collision\\Segment_Linear.h"

class TileEdgeArchetype_Linear : public TileEdgeArchetype {
    private:
        double x0;
        double y0;
        double x1;
        double y1;
    public:
        TileEdgeArchetype_Linear(double x0, double y0, double x1, double y1);
        TileEdgeArchetype* GeneratePerpArchetype() override;
        Segment* GenerateCollisionSegment(double xpos, double ypos, double halfWidth) override;
};