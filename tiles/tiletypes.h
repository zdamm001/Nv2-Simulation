#pragma once
#include <string>
#include <vector>

using namespace std;

class tiletypes {
    public:
        static inline const int EMPTY = 0;
        static inline const int FULL = 1;
        static inline const int HALF_TOP = 2;
        static inline const int HALF_RIGHT = 3;
        static inline const int HALF_BOTTOM = 4;
        static inline const int HALF_LEFT = 5;
        static inline const int MED_PP = 6;
        static inline const int MED_NP = 7;
        static inline const int MED_NN = 8;
        static inline const int MED_PN = 9;
        static inline const int CONVEX_PP = 10;
        static inline const int CONVEX_NP = 11;
        static inline const int CONVEX_NN = 12;
        static inline const int CONVEX_PN = 13;
        static inline const int CONCAVE_PP = 14;
        static inline const int CONCAVE_NP = 15;
        static inline const int CONCAVE_NN = 16;
        static inline const int CONCAVE_PN = 17;
        static inline const int SMALL_22_PP = 18;
        static inline const int SMALL_22_NP = 19;
        static inline const int SMALL_22_NN = 20;
        static inline const int SMALL_22_PN = 21;
        static inline const int LARGE_22_PP = 22;
        static inline const int LARGE_22_NP = 23;
        static inline const int LARGE_22_NN = 24;
        static inline const int LARGE_22_PN = 25;
        static inline const int SMALL_67_PP = 26;
        static inline const int SMALL_67_NP = 27;
        static inline const int SMALL_67_NN = 28;
        static inline const int SMALL_67_PN = 29;
        static inline const int LARGE_67_PP = 30;
        static inline const int LARGE_67_NP = 31;
        static inline const int LARGE_67_NN = 32;
        static inline const int LARGE_67_PN = 33;
        static inline const int EDGE_TOP = 34;
        static inline const int EDGE_RIGHT = 35;
        static inline const int EDGE_BOTTOM = 36;
        static inline const int EDGE_LEFT = 37;
        static inline const int EDGE_CORNER_UL = 38;
        static inline const int EDGE_CORNER_UR = 39;
        static inline const int EDGE_CORNER_DL = 40;
        static inline const int EDGE_CORNER_DR = 41;
        static inline const int num_tile_types = 42;
        static inline const int num_ingame_tile_types = 34;
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
        static void Initialize();
        static int GetTypeFromChar(int charIndex);
        static char GetDebugCharFromID(int id);
};