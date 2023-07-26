#include <cmath>
#include <string>

using namespace std;

class vec2 {
    public:
        double x;
        double y;

        vec2(double x = 0, double y = 0) : x(x), y(y) {}

        static vec2 FromDir(double radians) {
            return vec2(cos(radians), sin(radians));
        }

        static vec2 VecTo(const vec2& start, const vec2& end) {
            return vec2(end.x - start.x, end.y - start.y);
        }

        vec2 VecPerp(const vec2& v) {
            return vec2(-v.y, v.x);
        }

        double VecDot(const vec2& v1, const vec2& v2) {
            return v1.x * v2.x + v1.y * v2.y;
        }

        vec2 To(const vec2& end) {
            return vec2(end.x - x, end.y - y);
        }

        vec2 Perp() {
            return vec2(-y, x);
        }

        double PerpDot(const vec2& v) {
            return -y * v.x + x * v.y;
        }

        vec2 Clone() {
            return vec2(x, y);
        }

        vec2 Plus(const vec2& v) {
            return vec2(x + v.x, y + v.y);
        }

        vec2 Minus(const vec2& v) {
            return vec2(x - v.x, y - v.y);
        }

        double Dot(const vec2& v) {
            return x * v.x + y * v.y;
        }

        double Len() {
            return sqrt(x * x + y * y);
        }

        double LenSq() {
            return x * x + y * y;
        }

        string ToString() {
            return "(" + to_string(x) + "," + to_string(y) + ")";
        }

        void Copy(const vec2& v) {
            x = v.x;
            y = v.y;
        }

        void Normalize() {
            double length = sqrt(x * x + y * y);
            if (length != 0) {
                x /= length;
                y /= length;
            }
        }

        void Scale(double scalar) {
            x *= scalar;
            y *= scalar;
        }
};