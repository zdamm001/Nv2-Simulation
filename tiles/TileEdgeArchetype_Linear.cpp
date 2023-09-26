#include "TileEdgeArchetype_Linear.h"

TileEdgeArchetype_Linear::TileEdgeArchetype_Linear(double x0, double y0, double x1, double y1)
    : x0(x0), y0(y0), x1(x1), y1(y1) { }

TileEdgeArchetype* TileEdgeArchetype_Linear::GeneratePerpArchetype() {
    return new TileEdgeArchetype_Linear(-y0, x0, -y1, x1);
}

Segment* TileEdgeArchetype_Linear::GenerateCollisionSegment(double xpos, double ypos, double halfWidth) {
    return new Segment_Linear(xpos + x0 * halfWidth, ypos + y0 * halfWidth, xpos + x1 * halfWidth, ypos + y1 * halfWidth);
}