#pragma once

#include "AABB.h"
#include "..\\..\\math\\vec2.h"

class SimpleRenderer;

class Segment {
    public:
        virtual ~Segment() = default;
        virtual AABB GetAABB() const = 0;
        virtual void GetClosestPoint(const vec2& query_pos, vec2& out_closestpoint) = 0;
        virtual double IntersectWithRay(const vec2& ray_pos, const vec2& ray_vec, double ray_radius, vec2& OUT_intersection_pos, vec2& OUT_intersection_normal) = 0;
        virtual bool GetClosestPoint_IsBackfacing(const vec2& query_pos, vec2& out_closestpoint) = 0;
        virtual void DebugDraw(SimpleRenderer& rend) = 0;
        virtual void DebugDraw_NoStyle(SimpleRenderer& rend) = 0;
        virtual void DebugDraw_Simple(SimpleRenderer& rend) = 0;
};
