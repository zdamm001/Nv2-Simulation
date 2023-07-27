#include "vec2.h"

vec2::vec2(double x, double y) : x(x), y(y) {}

vec2 vec2::FromDir(double radians) {
    return vec2(cos(radians), sin(radians));
}

vec2 vec2::VecTo(const vec2& start, const vec2& end) {
    return vec2(end.x - start.x, end.y - start.y);
}

vec2 vec2::VecPerp(const vec2& v) {
    return vec2(-v.y, v.x);
}

double vec2::VecDot(const vec2& v1, const vec2& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

vec2 vec2::To(const vec2& end) {
    return vec2(end.x - x, end.y - y);
}

vec2 vec2::Perp() {
    return vec2(-y, x);
}

double vec2::PerpDot(const vec2& v) {
    return -y * v.x + x * v.y;
}

vec2 vec2::Clone() {
    return vec2(x, y);
}

vec2 vec2::Plus(const vec2& v) {
    return vec2(x + v.x, y + v.y);
}

vec2 vec2::Minus(const vec2& v) {
    return vec2(x - v.x, y - v.y);
}

double vec2::Dot(const vec2& v) {
    return x * v.x + y * v.y;
}

double vec2::Len() {
    return sqrt(x * x + y * y);
}

double vec2::LenSq() {
    return x * x + y * y;
}

string vec2::ToString() {
    return "(" + to_string(x) + "," + to_string(y) + ")";
}

void vec2::Copy(const vec2& v) {
    x = v.x;
    y = v.y;
}

void vec2::Normalize() {
    double length = sqrt(x * x + y * y);
    if (length != 0) {
        x /= length;
        y /= length;
    }
}

void vec2::Scale(double scalar) {
    x *= scalar;
    y *= scalar;
}