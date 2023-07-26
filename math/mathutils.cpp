#include <cmath>

using namespace std;

class mathutils {
    private:
        static unsigned int rnd_seed;
    public:
        mathutils() = delete;
        static void SetRandomSeed(unsigned int seedValue);
        static void GenerateNewRandomSeed();
        static unsigned int GetRandomSeed();
        static double Random();
    private:
        static unsigned int gen();
    public:
        static double DegToRad(double degrees);
        static double RadToDeg(double radians);
        static double WrapAngle_Shortest(double angle);
        static double WrapAngle_Directed(double angle, double direction);
        static double WrapAngle_Pos(double angle);
        static double InterpolateOrn(double startAngle, double endAngle, double factor, double direction = 0);
};

unsigned int mathutils::rnd_seed = 1;

void mathutils::SetRandomSeed(unsigned int seedValue) {
    if (seedValue == 0 || seedValue > 2147483646) {
        rnd_seed = 1;
    } else {
        rnd_seed = seedValue;
    }
}

void mathutils::GenerateNewRandomSeed() {
    unsigned int newSeed = 1 + static_cast<unsigned int>(rand() % 2147483645);
    SetRandomSeed(newSeed);
}

unsigned int mathutils::GetRandomSeed() {
    return rnd_seed;
}
      
double mathutils::Random() {
    return static_cast<double>(gen()) / 2147483647;
}

unsigned int mathutils::gen() {
    return rnd_seed = rnd_seed * 16807 % 2147483647;
}

double mathutils::DegToRad(double degrees) {
    return degrees * (M_PI / 180);
}

double mathutils::RadToDeg(double radians) {
    return radians * (180 / M_PI);
}

double mathutils::WrapAngle_Shortest(double angle) {
    while (abs(angle) > M_PI) {
        if (angle < 0) {
            angle += 2 * M_PI;
        } else {
            angle -= 2 * M_PI;
        }
    }
    return angle;
}

double mathutils::WrapAngle_Directed(double angle, double direction) {
    if (direction > 0) {
        return WrapAngle_Pos(angle);
    }
    if (direction < 0) {
        while (angle > 0 || angle < -2 * M_PI) {
            if (angle > 0) {
                angle -= 2 * M_PI;
            } else if (angle < -2 * M_PI) {
                angle += 2 * M_PI;
            }
        }
        return angle;
    }
    return 0;
}

double mathutils::WrapAngle_Pos(double angle) {
    while (angle < 0 || angle > 2 * M_PI) {
        if (angle < 0) {
            angle += 2 * M_PI;
        } else if (angle > 2 * M_PI) {
            angle -= 2 * M_PI;
        }
    }
    return angle;
}

double mathutils::InterpolateOrn(double startAngle, double endAngle, double factor, double direction = 0) {
    double wrappedStartAngle = WrapAngle_Pos(startAngle);
    double wrappedEndAngle = WrapAngle_Pos(endAngle);
    double angleDifference = (wrappedEndAngle - wrappedStartAngle);
    if (direction == 0) {
        angleDifference = WrapAngle_Shortest(angleDifference);
    } else {
        angleDifference = WrapAngle_Directed(angleDifference, direction);
    }
    angleDifference *= factor;
    return wrappedStartAngle + angleDifference;
}