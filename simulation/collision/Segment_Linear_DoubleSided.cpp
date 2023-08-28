#include "Segment_Linear_DoubleSided.h"

Segment_Linear_DoubleSided::Segment_Linear_DoubleSided(double x0, double y0, double x1, double y1)
    : Segment_Linear(x0, y0, x1, y1) {}

bool Segment_Linear_DoubleSided::GetClosestPoint_IsBackfacing(const vec2& query_pos, vec2& out_closestpoint) {
    Segment_Linear::GetClosestPoint_IsBackfacing(query_pos, out_closestpoint);
    return false;
}

void Segment_Linear_DoubleSided::DebugDraw_NoStyle(SimpleRenderer& rend) {
    //rend.DrawLine(p0.x, p0.y, p1.x, p1.y);

    //rend.DrawSquare(p0.x, p0.y, 2);
    //rend.DrawSquare(p1.x, p1.y, 2);

    vec2 v = p0.To(p1);
    vec2 n = v.Perp();
    n.Normalize();
    //rend.DrawLine(p0.x + 0.5 * v.x, p0.y + 0.5 * v.y, p0.x + 0.5 * v.x + 4 * n.x, p0.y + 0.5 * v.y + 4 * n.y);
    //rend.DrawLine(p0.x + 0.5 * v.x, p0.y + 0.5 * v.y, p0.x + 0.5 * v.x - 4 * n.x, p0.y + 0.5 * v.y - 4 * n.y);
}