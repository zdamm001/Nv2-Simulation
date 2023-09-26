#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>

using namespace std;

class vec2 {
    public:
        double x;
        double y;
    public:
        vec2(double x = 0, double y = 0);
        static vec2 FromDir(double radians);
        static vec2 VecTo(const vec2& start, const vec2& end);
        vec2 VecPerp(const vec2& v);
        double VecDot(const vec2& v1, const vec2& v2);
        vec2 To(const vec2& end) const;
        vec2 Perp() const;
        double PerpDot(const vec2& v) const;
        vec2 Clone() const;
        vec2 Plus(const vec2& v) const;
        vec2 Minus(const vec2& v) const;
        double Dot(const vec2& v) const;
        double Len() const;
        double LenSq() const;
        string ToString() const;
        void Copy(const vec2& v);
        void Normalize();
        void Scale(double scalar);
};