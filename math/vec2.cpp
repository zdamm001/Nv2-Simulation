#include <cmath>

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

        vec2 VecPerp(const vec2& vec) {
            return vec2(-vec.y, vec.x);
        }
};