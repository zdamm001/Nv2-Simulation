#include "Segment_Linear.h"

const vec2 Segment_Linear::zero_vec = vec2(0, 0);
vec2 Segment_Linear::cp = vec2();
vec2 Segment_Linear::ray_point = vec2();

Segment_Linear::Segment_Linear(double x0, double y0, double x1, double y1)
    : p0(x0, y0), p1(x1, y1), aabb(min(x0, x1), min(y0, y1), max(x0, x1), max(y0, y1)) { }

AABB Segment_Linear::GetAABB() const {
    return aabb;
}

void Segment_Linear::GetClosestPoint(const vec2& query_pos, vec2& out_closestpoint) {
    double v_X = p1.x - p0.x;
    double v_Y = p1.y - p0.y;

    double d_X = query_pos.x - p0.x;
    double d_Y = query_pos.y - p0.y;

    double dp = (v_X * d_X) + (v_Y * d_Y);
    double len2 = (v_X * v_X) + (v_Y * v_Y);

    if (dp <= 0) {
        out_closestpoint.Copy(p0);
    } else if (dp >= len2) {
        out_closestpoint.Copy(p1);
    } else {
        double t = dp / len2;
        out_closestpoint.x = p0.x + (t * v_X);
        out_closestpoint.y = p0.y + (t * v_Y);
    }
}

bool Segment_Linear::GetClosestPoint_IsBackfacing(const vec2& query_pos, vec2& out_closestpoint) {
    double v_X = p1.x - p0.x;
    double v_Y = p1.y - p0.y;

    double d_X = query_pos.x - p0.x;
    double d_Y = query_pos.y - p0.y;

    double dp = (v_X * d_X) + (v_Y * d_Y);
    double len2 = (v_X * v_X) + (v_Y * v_Y);

    if (dp <= 0) {
        out_closestpoint.Copy(p0);
    } else if (dp >= len2) {
        out_closestpoint.Copy(p1);
    } else {
        double t = dp / len2;
        out_closestpoint.x = p0.x + (t * v_X);
        out_closestpoint.y = p0.y + (t * v_Y);
    }

    return ((d_X * -v_Y) + (d_Y * v_X)) < 0;
}

double Segment_Linear::IntersectWithRay(const vec2& ray_pos, const vec2& ray_vec, double ray_radius, vec2& OUT_intersection_pos, vec2& OUT_intersection_normal) {
    double t0 = colutils::TimeOfIntersection_Circle_vs_Circle(ray_pos, ray_vec, p0, zero_vec, ray_radius);
    double t1 = colutils::TimeOfIntersection_Circle_vs_Circle(ray_pos, ray_vec, p1, zero_vec, ray_radius);
    double t2 = colutils::TimeOfIntersection_Point_vs_Lineseg(ray_pos, ray_vec, p0, p1, ray_radius);

    double tmin = min(t0, min(t1, t2));
    if (tmin <= 1 && tmin >= 0) {
        ray_point.x = ray_pos.x + (tmin * ray_vec.x);
        ray_point.y = ray_pos.y + (tmin * ray_vec.y);

        if (ray_radius > 0) {
            cp.x = 0;
            cp.y = 0;
            GetClosestPoint(ray_point, cp);

            double n_X = ray_point.x - cp.x;
            double n_Y = ray_point.y - cp.y;
            double nlen = sqrt((n_X * n_X) + (n_Y * n_Y));
            n_X /= nlen;
            n_Y /= nlen;

            OUT_intersection_pos.x = cp.x;
            OUT_intersection_pos.y = cp.y;
            OUT_intersection_normal.x = n_X;
            OUT_intersection_normal.y = n_Y;
        } else {
            double d_X = -(p1.y - p0.y);
            double d_Y = p1.x - p0.x;
            double dlen = sqrt((d_X * d_X) + (d_Y * d_Y));
            d_X /= dlen;
            d_Y /= dlen;

            if (((d_X * ray_vec.x) + (d_Y * ray_vec.y)) > 0) {
                d_X *= -1;
                d_Y *= -1;
            }

            OUT_intersection_pos.Copy(ray_point);
            OUT_intersection_normal.x = d_X;
            OUT_intersection_normal.y = d_Y;
        }
    }

    return tmin;
}

void Segment_Linear::DebugDraw(SimpleRenderer& rend) {
    //rend.SetStyle(0, 0x000000, 100);
    DebugDraw_NoStyle(rend);
}

void Segment_Linear::DebugDraw_Simple(SimpleRenderer& rend) {
    //rend.DrawLine(p0.x, p0.y, p1.x, p1.y);
}

void Segment_Linear::DebugDraw_NoStyle(SimpleRenderer& rend) {
    //rend.DrawLine(p0.x, p0.y, p1.x, p1.y);

    //rend.DrawSquare(p0.x, p0.y, 2);
    //rend.DrawSquare(p1.x, p1.y, 2);

    vec2 v = p1.To(p0);
    vec2 n = vec2(-v.y, v.x);
    n.Normalize();
    //rend.DrawLine(p0.x + 0.5 * v.x, p0.y + 0.5 * v.y, p0.x + 0.5 * v.x + 4 * n.x, p0.y + 0.5 * v.y + 4 * n.y);
}

Segment* Segment_Linear::Clone() const {
    return new Segment_Linear(p0.x, p0.y, p1.x, p1.y);
}