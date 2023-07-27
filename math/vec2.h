#pragma once
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
        vec2 To(const vec2& end);
        vec2 Perp();
        double PerpDot(const vec2& v);
        vec2 Clone();
        vec2 Plus(const vec2& v);
        vec2 Minus(const vec2& v);
        double Dot(const vec2& v);
        double Len();
        double LenSq();
        string ToString();
        void Copy(const vec2& v);
        void Normalize();
        void Scale(double scalar);
};