#include "edgedefs.h"

vector<int> edgedefs::edgestates_X(tiletypes::num_tile_types * 6);
vector<int> edgedefs::edgestates_Y(tiletypes::num_tile_types * 6);

void edgedefs::Initialize() {
    HELPER_SetEdgeStates_X(tiletypes::FULL,2,0,2,2,0,2);
    HELPER_SetEdgeStates_Y(tiletypes::FULL,2,0,2,2,0,2);
    HELPER_SetEdgeStates_Y(tiletypes::EDGE_BOTTOM,0,0,2,0,0,2);
    HELPER_SetEdgeStates_Rotate90(tiletypes::EDGE_BOTTOM,tiletypes::EDGE_LEFT);
    HELPER_SetEdgeStates_Rotate180(tiletypes::EDGE_BOTTOM,tiletypes::EDGE_TOP);
    HELPER_SetEdgeStates_Rotate270(tiletypes::EDGE_BOTTOM,tiletypes::EDGE_RIGHT);
    HELPER_SetEdgeStates_X(tiletypes::HALF_BOTTOM,0,0,0,2,0,2);
    HELPER_SetEdgeStates_Y(tiletypes::HALF_BOTTOM,0,2,2,0,2,2);
    HELPER_SetEdgeStates_Rotate90(tiletypes::HALF_BOTTOM,tiletypes::HALF_LEFT);
    HELPER_SetEdgeStates_Rotate180(tiletypes::HALF_BOTTOM,tiletypes::HALF_TOP);
    HELPER_SetEdgeStates_Rotate270(tiletypes::HALF_BOTTOM,tiletypes::HALF_RIGHT);
    HELPER_SetEdgeStates_X(tiletypes::CONCAVE_PP,2,0,1,2,1,0);
    HELPER_SetEdgeStates_Y(tiletypes::CONCAVE_PP,2,0,1,2,1,0);
    HELPER_SetEdgeStates_Rotate90(tiletypes::CONCAVE_PP,tiletypes::CONCAVE_NP);
    HELPER_SetEdgeStates_Rotate180(tiletypes::CONCAVE_PP,tiletypes::CONCAVE_NN);
    HELPER_SetEdgeStates_Rotate270(tiletypes::CONCAVE_PP,tiletypes::CONCAVE_PN);
    HELPER_SetEdgeStates_X(tiletypes::CONVEX_PP,2,0,1,2,0,1);
    HELPER_SetEdgeStates_Y(tiletypes::CONVEX_PP,2,0,1,2,0,1);
    HELPER_SetEdgeStates_Rotate90(tiletypes::CONVEX_PP,tiletypes::CONVEX_NP);
    HELPER_SetEdgeStates_Rotate180(tiletypes::CONVEX_PP,tiletypes::CONVEX_NN);
    HELPER_SetEdgeStates_Rotate270(tiletypes::CONVEX_PP,tiletypes::CONVEX_PN);
    HELPER_SetEdgeStates_Copy(tiletypes::CONCAVE_PP,tiletypes::MED_PP);
    HELPER_SetEdgeStates_Copy(tiletypes::CONCAVE_NP,tiletypes::MED_NP);
    HELPER_SetEdgeStates_Copy(tiletypes::CONCAVE_NN,tiletypes::MED_NN);
    HELPER_SetEdgeStates_Copy(tiletypes::CONCAVE_PN,tiletypes::MED_PN);
    HELPER_SetEdgeStates_X(tiletypes::SMALL_22_PP,2,0,1,0,0,0);
    HELPER_SetEdgeStates_Y(tiletypes::SMALL_22_PP,2,1,0,2,1,0);
    HELPER_SetEdgeStates_Rotate90(tiletypes::SMALL_22_PP,tiletypes::SMALL_67_NP);
    HELPER_SetEdgeStates_Rotate180(tiletypes::SMALL_22_PP,tiletypes::SMALL_22_NN);
    HELPER_SetEdgeStates_Rotate270(tiletypes::SMALL_22_PP,tiletypes::SMALL_67_PN);
    HELPER_SetEdgeStates_X(tiletypes::SMALL_67_PP,2,1,0,2,1,0);
    HELPER_SetEdgeStates_Y(tiletypes::SMALL_67_PP,2,0,1,0,0,0);
    HELPER_SetEdgeStates_Rotate90(tiletypes::SMALL_67_PP,tiletypes::SMALL_22_NP);
    HELPER_SetEdgeStates_Rotate180(tiletypes::SMALL_67_PP,tiletypes::SMALL_67_NN);
    HELPER_SetEdgeStates_Rotate270(tiletypes::SMALL_67_PP,tiletypes::SMALL_22_PN);
    HELPER_SetEdgeStates_X(tiletypes::LARGE_22_PP,2,0,2,2,0,1);
    HELPER_SetEdgeStates_Y(tiletypes::LARGE_22_PP,2,0,1,2,0,1);
    HELPER_SetEdgeStates_Rotate90(tiletypes::LARGE_22_PP,tiletypes::LARGE_67_NP);
    HELPER_SetEdgeStates_Rotate180(tiletypes::LARGE_22_PP,tiletypes::LARGE_22_NN);
    HELPER_SetEdgeStates_Rotate270(tiletypes::LARGE_22_PP,tiletypes::LARGE_67_PN);
    HELPER_SetEdgeStates_X(tiletypes::LARGE_67_PP,2,0,1,2,0,1);
    HELPER_SetEdgeStates_Y(tiletypes::LARGE_67_PP,2,0,2,2,0,1);
    HELPER_SetEdgeStates_Rotate90(tiletypes::LARGE_67_PP,tiletypes::LARGE_22_NP);
    HELPER_SetEdgeStates_Rotate180(tiletypes::LARGE_67_PP,tiletypes::LARGE_67_NN);
    HELPER_SetEdgeStates_Rotate270(tiletypes::LARGE_67_PP,tiletypes::LARGE_22_PN);
}

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
