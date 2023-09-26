#pragma once

#include "..\\simulation\\collision\\Segment.h"

class TileEdgeArchetype {
    public:
        virtual ~TileEdgeArchetype() = default;
        virtual TileEdgeArchetype* GeneratePerpArchetype() = 0;
        virtual Segment* GenerateCollisionSegment(double xpos, double ypos, double halfWidth) = 0;
};