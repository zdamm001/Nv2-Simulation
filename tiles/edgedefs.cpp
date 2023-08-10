#include "edgedefs.h"

vector<int> edgedefs::edgestates_X(tiletypes::num_tile_types * 6);
vector<int> edgedefs::edgestates_Y(tiletypes::num_tile_types * 6);

int edgedefs::GetEdgeState_X(int tileID, int offset) {
    return edgestates_X[tileID * 6 + offset];
}

int edgedefs::GetEdgeState_Y(int tileID, int offset) {
    return edgestates_Y[tileID * 6 + offset];
}

void edgedefs::HELPER_SetEdgeStates_X(int tileType, int state0, int state1, int state2, int state3, int state4, int state5) {
    int index = tileType * 6;
    edgestates_X[index + 0] = state0;
    edgestates_X[index + 1] = state1;
    edgestates_X[index + 2] = state2;
    edgestates_X[index + 3] = state3;
    edgestates_X[index + 4] = state4;
    edgestates_X[index + 5] = state5;
}

void edgedefs::HELPER_SetEdgeStates_Y(int tileType, int state0, int state1, int state2, int state3, int state4, int state5) {
    int index = tileType * 6;
    edgestates_Y[index + 0] = state0;
    edgestates_Y[index + 1] = state1;
    edgestates_Y[index + 2] = state2;
    edgestates_Y[index + 3] = state3;
    edgestates_Y[index + 4] = state4;
    edgestates_Y[index + 5] = state5;
}

void edgedefs::HELPER_SetEdgeStates_Copy(int sourceType, int targetType) {
    int sourceIndex = sourceType * 6;
    int targetIndex = targetType * 6;

    edgestates_X[targetIndex + 0] = edgestates_X[sourceIndex + 0];
    edgestates_X[targetIndex + 1] = edgestates_X[sourceIndex + 1];
    edgestates_X[targetIndex + 2] = edgestates_X[sourceIndex + 2];
    edgestates_X[targetIndex + 3] = edgestates_X[sourceIndex + 3];
    edgestates_X[targetIndex + 4] = edgestates_X[sourceIndex + 4];
    edgestates_X[targetIndex + 5] = edgestates_X[sourceIndex + 5];

    edgestates_Y[targetIndex + 0] = edgestates_Y[sourceIndex + 0];
    edgestates_Y[targetIndex + 1] = edgestates_Y[sourceIndex + 1];
    edgestates_Y[targetIndex + 2] = edgestates_Y[sourceIndex + 2];
    edgestates_Y[targetIndex + 3] = edgestates_Y[sourceIndex + 3];
    edgestates_Y[targetIndex + 4] = edgestates_Y[sourceIndex + 4];
    edgestates_Y[targetIndex + 5] = edgestates_Y[sourceIndex + 5];
}

void edgedefs::HELPER_SetEdgeStates_Rotate90(int sourceType, int targetType) {
    int sourceIndex = sourceType * 6;
    int targetIndex = targetType * 6;

    edgestates_Y[targetIndex + 0] = edgestates_X[sourceIndex + 3];
    edgestates_Y[targetIndex + 1] = edgestates_X[sourceIndex + 4];
    edgestates_Y[targetIndex + 2] = edgestates_X[sourceIndex + 5];
    edgestates_Y[targetIndex + 3] = edgestates_X[sourceIndex + 0];
    edgestates_Y[targetIndex + 4] = edgestates_X[sourceIndex + 1];
    edgestates_Y[targetIndex + 5] = edgestates_X[sourceIndex + 2];
    edgestates_X[targetIndex + 0] = edgestates_Y[sourceIndex + 2];
    edgestates_X[targetIndex + 1] = edgestates_Y[sourceIndex + 1];
    edgestates_X[targetIndex + 2] = edgestates_Y[sourceIndex + 0];
    edgestates_X[targetIndex + 3] = edgestates_Y[sourceIndex + 5];
    edgestates_X[targetIndex + 4] = edgestates_Y[sourceIndex + 4];
    edgestates_X[targetIndex + 5] = edgestates_Y[sourceIndex + 3];
}

void edgedefs::HELPER_SetEdgeStates_Rotate180(int sourceType, int targetType) {
    int sourceIndex = sourceType * 6;
    int targetIndex = targetType * 6;

    edgestates_X[targetIndex + 0] = edgestates_X[sourceIndex + 5];
    edgestates_X[targetIndex + 1] = edgestates_X[sourceIndex + 4];
    edgestates_X[targetIndex + 2] = edgestates_X[sourceIndex + 3];
    edgestates_X[targetIndex + 3] = edgestates_X[sourceIndex + 2];
    edgestates_X[targetIndex + 4] = edgestates_X[sourceIndex + 1];
    edgestates_X[targetIndex + 5] = edgestates_X[sourceIndex + 0];
    edgestates_Y[targetIndex + 0] = edgestates_Y[sourceIndex + 5];
    edgestates_Y[targetIndex + 1] = edgestates_Y[sourceIndex + 4];
    edgestates_Y[targetIndex + 2] = edgestates_Y[sourceIndex + 3];
    edgestates_Y[targetIndex + 3] = edgestates_Y[sourceIndex + 2];
    edgestates_Y[targetIndex + 4] = edgestates_Y[sourceIndex + 1];
    edgestates_Y[targetIndex + 5] = edgestates_Y[sourceIndex + 0];
}

void edgedefs::HELPER_SetEdgeStates_Rotate270(int sourceType, int targetType) {
    int sourceIndex = sourceType * 6;
    int targetIndex = targetType * 6;

    edgestates_Y[targetIndex + 0] = edgestates_X[sourceIndex + 2];
    edgestates_Y[targetIndex + 1] = edgestates_X[sourceIndex + 1];
    edgestates_Y[targetIndex + 2] = edgestates_X[sourceIndex + 0];
    edgestates_Y[targetIndex + 3] = edgestates_X[sourceIndex + 5];
    edgestates_Y[targetIndex + 4] = edgestates_X[sourceIndex + 4];
    edgestates_Y[targetIndex + 5] = edgestates_X[sourceIndex + 3];
    edgestates_X[targetIndex + 0] = edgestates_Y[sourceIndex + 3];
    edgestates_X[targetIndex + 1] = edgestates_Y[sourceIndex + 4];
    edgestates_X[targetIndex + 2] = edgestates_Y[sourceIndex + 5];
    edgestates_X[targetIndex + 3] = edgestates_Y[sourceIndex + 0];
    edgestates_X[targetIndex + 4] = edgestates_Y[sourceIndex + 1];
    edgestates_X[targetIndex + 5] = edgestates_Y[sourceIndex + 2];
}
