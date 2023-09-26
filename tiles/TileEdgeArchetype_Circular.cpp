#include "TileEdgeArchetype_Circular.h"

TileEdgeArchetype_Circular::TileEdgeArchetype_Circular(double x0, double y0, double x1, double y1, double x2, double y2)
    : x0(x0), y0(y0), x1(x1), y1(y1), x2(x2), y2(y2) { }

TileEdgeArchetype* TileEdgeArchetype_Circular::GeneratePerpArchetype() {
    return new TileEdgeArchetype_Circular(-y0, x0, -y1, x1, -y2, x2);
}

Segment* TileEdgeArchetype_Circular::GenerateCollisionSegment(double xpos, double ypos, double halfWidth) {
    return new Segment_Circular(xpos + x2 * halfWidth, ypos + y2 * halfWidth, xpos + x0 * halfWidth, ypos + y0 * halfWidth, xpos + x1 * halfWidth, ypos + y1 * halfWidth);
}