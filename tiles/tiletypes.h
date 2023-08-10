#pragma once
#include <string>
#include <vector>

using namespace std;

class tiletypes {
    public:
        static const int EMPTY = 0;
        static const int FULL = 1;
        static const int HALF_TOP = 2;
        static const int HALF_RIGHT = 3;
        static const int HALF_BOTTOM = 4;
        static const int HALF_LEFT = 5;
        static const int MED_PP = 6;
        static const int MED_NP = 7;
        static const int MED_NN = 8;
        static const int MED_PN = 9;
        static const int CONVEX_PP = 10;
        static const int CONVEX_NP = 11;
        static const int CONVEX_NN = 12;
        static const int CONVEX_PN = 13;
        static const int CONCAVE_PP = 14;
        static const int CONCAVE_NP = 15;
        static const int CONCAVE_NN = 16;
        static const int CONCAVE_PN = 17;
        static const int SMALL_22_PP = 18;
        static const int SMALL_22_NP = 19;
        static const int SMALL_22_NN = 20;
        static const int SMALL_22_PN = 21;
        static const int LARGE_22_PP = 22;
        static const int LARGE_22_NP = 23;
        static const int LARGE_22_NN = 24;
        static const int LARGE_22_PN = 25;
        static const int SMALL_67_PP = 26;
        static const int SMALL_67_NP = 27;
        static const int SMALL_67_NN = 28;
        static const int SMALL_67_PN = 29;
        static const int LARGE_67_PP = 30;
        static const int LARGE_67_NP = 31;
        static const int LARGE_67_NN = 32;
        static const int LARGE_67_PN = 33;
        static const int EDGE_TOP = 34;
        static const int EDGE_RIGHT = 35;
        static const int EDGE_BOTTOM = 36;
        static const int EDGE_LEFT = 37;
        static const int EDGE_CORNER_UL = 38;
        static const int EDGE_CORNER_UR = 39;
        static const int EDGE_CORNER_DL = 40;
        static const int EDGE_CORNER_DR = 41;
        static const int num_tile_types = 42;
        static const int num_ingame_tile_types = 34;
    private:
        static vector<int> MAP_OLD_TYPE_TO_NEW_TYPE;
        static vector<string> MAP_NEW_TYPE_TO_CHAR;
        static const string hacky_debug_chars;
    public:
        static vector<int> XFORM_INVERT;
        static vector<int> XFORM_ROTCW;
        static vector<int> XFORM_ROTCCW;
        static vector<int> XFORM_FLIPH;
        static vector<int> XFORM_FLIPV;
    public:
        tiletypes() = delete;
        int GetTypeFromChar(int charIndex);
        char GetDebugCharFromID(int id);
};