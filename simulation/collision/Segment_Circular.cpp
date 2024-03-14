#include "Segment_Circular.h"

const vec2 Segment_Circular::zero_vec = vec2(0, 0);
vec2 Segment_Circular::cp = vec2();
vec2 Segment_Circular::ray_point = vec2();

Segment_Circular::Segment_Circular(double x_center, double y_center, double x0, double y0, double x1, double y1)
    : p0(x0, y0), p1(x1, y1), pC(x_center, y_center), aabb(min(p0.x, p1.x), min(p0.y, p1.y), max(p0.x, p1.x), max(p0.y, p1.y)) {}

AABB Segment_Circular::GetAABB() const {
    return aabb;
}

void Segment_Circular::GetClosestPoint(const vec2& query_pos, vec2& out_closestpoint) {
    double v0_X = p0.x - pC.x;
    double v0_Y = p0.y - pC.y;

    double v1_X = p1.x - pC.x;
    double v1_Y = p1.y - pC.y;

    double d_X = query_pos.x - pC.x;
    double d_Y = query_pos.y - pC.y;

    double dp0 = (d_X * -v0_Y) + (d_Y * v0_X);
    double dp1 = (d_X * -v1_Y) + (d_Y * v1_X);

    double v_X = p1.x - p0.x;
    double v_Y = p1.y - p0.y;

    double vp0 = (v_X * -v0_Y) + (v_Y * v0_X);
    double vp1 = (v_X * -v1_Y) + (v_Y * v1_X);

    bool in0 = (dp0 * vp0 <= 0);
    bool in1 = (dp1 * vp1 >= 0);

    if (in0) {
        if (in1) {
            if (((d_X * v_X) + (d_Y * v_Y)) <= 0) {
                out_closestpoint.Copy(p0);
            } else {
                out_closestpoint.Copy(p1);
            }
        } else {
            out_closestpoint.Copy(p0);
        }
    } else if (in1) {
        out_closestpoint.Copy(p1);
    } else {
        double radius = sqrt((v0_X * v0_X) + (v0_Y * v0_Y));
        double dlen = sqrt((d_X * d_X) + (d_Y * d_Y));
        d_X /= dlen;
        d_Y /= dlen;
        d_X *= radius;
        d_Y *= radius;

        out_closestpoint.x = pC.x + d_X;
        out_closestpoint.y = pC.y + d_Y;
    }
}

bool Segment_Circular::GetClosestPoint_IsBackfacing(const vec2& query_pos, vec2& out_closestpoint) {
    double v0_X = p0.x - pC.x;
    double v0_Y = p0.y - pC.y;

    double v1_X = p1.x - pC.x;
    double v1_Y = p1.y - pC.y;

    double d_X = query_pos.x - pC.x;
    double d_Y = query_pos.y - pC.y;

    double dp0 = (d_X * -v0_Y) + (d_Y * v0_X);
    double dp1 = (d_X * -v1_Y) + (d_Y * v1_X);

    double v_X = p1.x - p0.x;
    double v_Y = p1.y - p0.y;

    double vp0 = (v_X * -v0_Y) + (v_Y * v0_X);
    double vp1 = (v_X * -v1_Y) + (v_Y * v1_X);

    bool in0 = (dp0 * vp0 <= 0);
    bool in1 = (dp1 * vp1 >= 0);

    int closest_vertex = -1;
    if (in0) {
        if (in1) {
            if (((d_X * v_X) + (d_Y * v_Y)) <= 0) {
                out_closestpoint.Copy(p0);
                closest_vertex = 0;
            } else {
                out_closestpoint.Copy(p1);
                closest_vertex = 1;
            }
        } else {
            out_closestpoint.Copy(p0);
            closest_vertex = 0;
        }
    } else if (in1) {
        out_closestpoint.Copy(p1);
        closest_vertex = 1;
    } else {
        double radius = sqrt((v0_X * v0_X) + (v0_Y * v0_Y));
        double dlen = sqrt((d_X * d_X) + (d_Y * d_Y));
        d_X /= dlen;
        d_Y /= dlen;
        d_X *= radius;
        d_Y *= radius;

        out_closestpoint.x = pC.x + d_X;
        out_closestpoint.y = pC.y + d_Y;
    }

    double to_closest_point_X = out_closestpoint.x - query_pos.x;
    double to_closest_point_Y = out_closestpoint.y - query_pos.y;

    if (closest_vertex < 0) {
        return (((to_closest_point_X * -v_Y) + (to_closest_point_Y * v_X)) > 0);
    } else {
        double line_n_X = v0_X;
        double line_n_Y = v0_Y;

        if (closest_vertex == 1) {
            line_n_X = v1_X;
            line_n_Y = v1_Y;
        }

        if (((line_n_X * -v_Y) + (line_n_Y * v_X)) < 0) {
            line_n_X *= -1;
            line_n_Y *= -1;
        }

        return (((to_closest_point_X * line_n_X) + (to_closest_point_Y * line_n_Y)) > 0);
    }
}

double Segment_Circular::IntersectWithRay(const vec2& ray_pos, const vec2& ray_vec, double ray_radius, vec2& OUT_intersection_pos, vec2& OUT_intersection_normal) {
    double t0 = colutils::TimeOfIntersection_Circle_vs_Circle(ray_pos, ray_vec, p0, zero_vec, ray_radius);
    double t1 = colutils::TimeOfIntersection_Circle_vs_Circle(ray_pos, ray_vec, p1, zero_vec, ray_radius);
    double t2 = 2;
    
    GetClosestPoint(ray_pos, cp);
    
    double temp_dx = ray_pos.x - cp.x;
    double temp_dy = ray_pos.y - cp.y;
    double temp_len = sqrt((temp_dx * temp_dx) + (temp_dy * temp_dy));
    if (temp_len <= ray_radius) {
        t2 = -1;
    } else {
        t2 = colutils::TimeOfIntersection_Circle_vs_Arc(ray_pos, ray_vec, pC, p0, p1, ray_radius);
    }
    
    double tmin = min(min(t0, t1), t2);
    
    if (tmin <= 1 && tmin >= 0) {
        ray_point.x = ray_pos.x + (tmin * ray_vec.x);
        ray_point.y = ray_pos.y + (tmin * ray_vec.y);
        
        if (ray_radius > 0) {
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
            double d_X = ray_point.x - pC.x;
            double d_Y = ray_point.y - pC.y;
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

void Segment_Circular::DebugDraw(SimpleRenderer& rend) {
    //rend.SetStyle(0, 0x000000, 100);
    DebugDraw_NoStyle(rend);
}

void Segment_Circular::DebugDraw_Simple(SimpleRenderer& rend) {
    //rend.DrawCircularArc_Convex(pC.x, pC.y, p0.x, p0.y, p1.x, p1.y, pC.To(p0).Len());
}

void Segment_Circular::DebugDraw_NoStyle(SimpleRenderer& rend) {
    //rend.DrawCircularArc_Convex(pC.x, pC.y, p0.x, p0.y, p1.x, p1.y, pC.To(p0).Len());

    //rend.DrawSquare(p0.x, p0.y, 2);
    //rend.DrawSquare(p1.x, p1.y, 2);
    //rend.DrawPlus(pC.x, pC.y, 2);

    double radius = pC.To(p0).Len();
    vec2 v = p0.To(p1);
    vec2 n = v.Perp();
    n.Normalize();
    v.Scale(0.5);
    vec2 d = pC.To(p0.Plus(v));
    d.Normalize();
    d.Scale(radius);
    //rend.DrawLine(pC.x + d.x, pC.y + d.y, pC.x + d.x + 4 * n.x, pC.y + d.y + 4 * n.y);
}

Segment* Segment_Circular::Clone() const {
    return new Segment_Circular(pC.x, pC.y, p0.x, p0.y, p1.x, p1.y);
}