#pragma once
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