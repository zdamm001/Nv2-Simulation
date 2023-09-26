#pragma once
#include <vector>

using namespace std;

class BitmapData;

class Flavours {
    private:
        static vector<unsigned int> _p1Colors;
        static vector<unsigned int> _p2Colors;
        static BitmapData* _flavourImage;
    public:
        Flavours() = delete;
        static unsigned int getP1Flavour(int color);
        static unsigned int getP2Flavour(int color);
    private:
        static void readImage();
};
