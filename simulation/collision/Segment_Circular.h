#pragma once

#include "..\\..\\math\\vec2.h"
#include "AABB.h"
#include "Segment.h"
#include "colutils.h"

class Segment_Circular : public Segment {
    private:
        static const vec2 zero_vec;
        static vec2 cp;
        static vec2 ray_point;
        vec2 p0;
        vec2 p1;
        vec2 pC;
        AABB aabb;
    public:
        Segment_Circular(double x_center, double y_center, double x0, double y0, double x1, double y1);
        AABB GetAABB() const override;
        void GetClosestPoint(const vec2& query_pos, vec2& out_closestpoint) override;
        bool GetClosestPoint_IsBackfacing(const vec2& query_pos, vec2& out_closestpoint) override;
        double IntersectWithRay(const vec2& ray_pos, const vec2& ray_vec, double ray_radius, vec2& OUT_intersection_pos, vec2& OUT_intersection_normal) override;
        void DebugDraw(SimpleRenderer& rend) override;
        void DebugDraw_Simple(SimpleRenderer& rend) override;
        void DebugDraw_NoStyle(SimpleRenderer& rend) override;
};