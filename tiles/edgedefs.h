#pragma once
#include <vector>

using namespace std;

#include "tiletypes.h"

class edgedefs {
    private:
        static vector<int> edgestates_X;
        static vector<int> edgestates_Y;
    public:
        edgedefs() = delete;
        static int GetEdgeState_X(int tileID, int offset);
        static int GetEdgeState_Y(int tileID, int offset);
    private:
        static void HELPER_SetEdgeStates_X(int tileType, int state0, int state1, int state2, int state3, int state4, int state5);
        static void HELPER_SetEdgeStates_Y(int tileType, int state0, int state1, int state2, int state3, int state4, int state5);
        static void HELPER_SetEdgeStates_Copy(int sourceType, int targetType);
        static void HELPER_SetEdgeStates_Rotate90(int sourceType, int targetType);
        static void HELPER_SetEdgeStates_Rotate180(int sourceType, int targetType);
        static void HELPER_SetEdgeStates_Rotate270(int sourceType, int targetType);
};