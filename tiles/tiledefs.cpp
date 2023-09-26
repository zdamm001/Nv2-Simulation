#include "tiledefs.h"

vector<TileEdgeArchetype*> tiledefs::segdefs(tiletypes::num_tile_types, nullptr);
vector<unsigned int> tiledefs::perpindex(8);
vector<vector<bool>> tiledefs::boundaryflags(tiletypes::num_tile_types, vector<bool>(8));
vector<TileEdgeArchetype*> tiledefs::boundarydefs(12, nullptr);

void tiledefs::Initialize() {
    segdefs[tiletypes::EMPTY] = nullptr;
    segdefs[tiletypes::FULL] = nullptr;
    segdefs[tiletypes::EDGE_TOP] = nullptr;
    segdefs[tiletypes::EDGE_RIGHT] = nullptr;
    segdefs[tiletypes::EDGE_BOTTOM] = nullptr;
    segdefs[tiletypes::EDGE_LEFT] = nullptr;
    segdefs[tiletypes::EDGE_CORNER_UL] = nullptr;
    segdefs[tiletypes::EDGE_CORNER_UR] = nullptr;
    segdefs[tiletypes::EDGE_CORNER_DL] = nullptr;
    segdefs[tiletypes::EDGE_CORNER_DR] = nullptr;
    segdefs[tiletypes::HALF_TOP] = new TileEdgeArchetype_Linear(-1,0,1,0);
    segdefs[tiletypes::HALF_RIGHT] = segdefs[tiletypes::HALF_TOP]->GeneratePerpArchetype();
    segdefs[tiletypes::HALF_BOTTOM] = segdefs[tiletypes::HALF_RIGHT]->GeneratePerpArchetype();
    segdefs[tiletypes::HALF_LEFT] = segdefs[tiletypes::HALF_BOTTOM]->GeneratePerpArchetype();
    segdefs[tiletypes::MED_PP] = new TileEdgeArchetype_Linear(-1,1,1,-1);
    segdefs[tiletypes::MED_NP] = segdefs[tiletypes::MED_PP]->GeneratePerpArchetype();
    segdefs[tiletypes::MED_NN] = segdefs[tiletypes::MED_NP]->GeneratePerpArchetype();
    segdefs[tiletypes::MED_PN] = segdefs[tiletypes::MED_NN]->GeneratePerpArchetype();
    segdefs[tiletypes::CONVEX_PP] = new TileEdgeArchetype_Circular(-1,1,1,-1,-1,-1);
    segdefs[tiletypes::CONVEX_NP] = segdefs[tiletypes::CONVEX_PP]->GeneratePerpArchetype();
    segdefs[tiletypes::CONVEX_NN] = segdefs[tiletypes::CONVEX_NP]->GeneratePerpArchetype();
    segdefs[tiletypes::CONVEX_PN] = segdefs[tiletypes::CONVEX_NN]->GeneratePerpArchetype();
    segdefs[tiletypes::CONCAVE_PP] = new TileEdgeArchetype_Circular(-1,1,1,-1,1,1);
    segdefs[tiletypes::CONCAVE_NP] = segdefs[tiletypes::CONCAVE_PP]->GeneratePerpArchetype();
    segdefs[tiletypes::CONCAVE_NN] = segdefs[tiletypes::CONCAVE_NP]->GeneratePerpArchetype();
    segdefs[tiletypes::CONCAVE_PN] = segdefs[tiletypes::CONCAVE_NN]->GeneratePerpArchetype();
    segdefs[tiletypes::SMALL_22_PP] = new TileEdgeArchetype_Linear(-1,0,1,-1);
    segdefs[tiletypes::SMALL_67_NP] = segdefs[tiletypes::SMALL_22_PP]->GeneratePerpArchetype();
    segdefs[tiletypes::SMALL_22_NN] = segdefs[tiletypes::SMALL_67_NP]->GeneratePerpArchetype();
    segdefs[tiletypes::SMALL_67_PN] = segdefs[tiletypes::SMALL_22_NN]->GeneratePerpArchetype();
    segdefs[tiletypes::SMALL_67_PP] = new TileEdgeArchetype_Linear(-1,1,0,-1);
    segdefs[tiletypes::SMALL_22_NP] = segdefs[tiletypes::SMALL_67_PP]->GeneratePerpArchetype();
    segdefs[tiletypes::SMALL_67_NN] = segdefs[tiletypes::SMALL_22_NP]->GeneratePerpArchetype();
    segdefs[tiletypes::SMALL_22_PN] = segdefs[tiletypes::SMALL_67_NN]->GeneratePerpArchetype();
    segdefs[tiletypes::LARGE_22_PP] = new TileEdgeArchetype_Linear(-1,1,1,0);
    segdefs[tiletypes::LARGE_67_NP] = segdefs[tiletypes::LARGE_22_PP]->GeneratePerpArchetype();
    segdefs[tiletypes::LARGE_22_NN] = segdefs[tiletypes::LARGE_67_NP]->GeneratePerpArchetype();
    segdefs[tiletypes::LARGE_67_PN] = segdefs[tiletypes::LARGE_22_NN]->GeneratePerpArchetype();
    segdefs[tiletypes::LARGE_67_PP] = new TileEdgeArchetype_Linear(0,1,1,-1);
    segdefs[tiletypes::LARGE_22_NP] = segdefs[tiletypes::LARGE_67_PP]->GeneratePerpArchetype();
    segdefs[tiletypes::LARGE_67_NN] = segdefs[tiletypes::LARGE_22_NP]->GeneratePerpArchetype();
    segdefs[tiletypes::LARGE_22_PN] = segdefs[tiletypes::LARGE_67_NN]->GeneratePerpArchetype();
    perpindex[0] = 2;
    perpindex[1] = 3;
    perpindex[2] = 5;
    perpindex[3] = 4;
    perpindex[4] = 6;
    perpindex[5] = 7;
    perpindex[6] = 1;
    perpindex[7] = 0;
    HELPER_InitBoundaryFlags();
    boundaryflags[tiletypes::FULL][0] = true; //left bottom half
    boundaryflags[tiletypes::FULL][1] = true; //left top half
    boundaryflags[tiletypes::FULL][2] = true; //top left half
    boundaryflags[tiletypes::FULL][3] = true; //top right half
    boundaryflags[tiletypes::FULL][4] = true; //right bottom half
    boundaryflags[tiletypes::FULL][5] = true; //right top half
    boundaryflags[tiletypes::FULL][6] = true; //bottom left half
    boundaryflags[tiletypes::FULL][7] = true; //bottom right half
    boundaryflags[tiletypes::EDGE_TOP][6] = true;
    boundaryflags[tiletypes::EDGE_TOP][7] = true;
    HELPER_SetBoundaryFlags_Perp(tiletypes::EDGE_TOP,tiletypes::EDGE_RIGHT);
    HELPER_SetBoundaryFlags_Perp(tiletypes::EDGE_RIGHT,tiletypes::EDGE_BOTTOM);
    HELPER_SetBoundaryFlags_Perp(tiletypes::EDGE_BOTTOM,tiletypes::EDGE_LEFT);
    boundaryflags[tiletypes::HALF_TOP][0] = true;
    boundaryflags[tiletypes::HALF_TOP][4] = true;
    boundaryflags[tiletypes::HALF_TOP][6] = true;
    boundaryflags[tiletypes::HALF_TOP][7] = true;
    HELPER_SetBoundaryFlags_Perp(tiletypes::HALF_TOP,tiletypes::HALF_RIGHT);
    HELPER_SetBoundaryFlags_Perp(tiletypes::HALF_RIGHT,tiletypes::HALF_BOTTOM);
    HELPER_SetBoundaryFlags_Perp(tiletypes::HALF_BOTTOM,tiletypes::HALF_LEFT);
    boundaryflags[tiletypes::MED_PP][0] = true;
    boundaryflags[tiletypes::MED_PP][1] = true;
    boundaryflags[tiletypes::MED_PP][6] = true;
    boundaryflags[tiletypes::MED_PP][7] = true;
    HELPER_SetBoundaryFlags_Perp(tiletypes::MED_PP,tiletypes::MED_NP);
    HELPER_SetBoundaryFlags_Perp(tiletypes::MED_NP,tiletypes::MED_NN);
    HELPER_SetBoundaryFlags_Perp(tiletypes::MED_NN,tiletypes::MED_PN);
    HELPER_SetBoundaryFlags_Copy(tiletypes::MED_PP,tiletypes::CONVEX_PP);
    HELPER_SetBoundaryFlags_Copy(tiletypes::MED_NP,tiletypes::CONVEX_NP);
    HELPER_SetBoundaryFlags_Copy(tiletypes::MED_NN,tiletypes::CONVEX_NN);
    HELPER_SetBoundaryFlags_Copy(tiletypes::MED_PN,tiletypes::CONVEX_PN);
    HELPER_SetBoundaryFlags_Copy(tiletypes::MED_PP,tiletypes::CONCAVE_PP);
    HELPER_SetBoundaryFlags_Copy(tiletypes::MED_NP,tiletypes::CONCAVE_NP);
    HELPER_SetBoundaryFlags_Copy(tiletypes::MED_NN,tiletypes::CONCAVE_NN);
    HELPER_SetBoundaryFlags_Copy(tiletypes::MED_PN,tiletypes::CONCAVE_PN);
    boundaryflags[tiletypes::SMALL_22_PP][0] = true;
    boundaryflags[tiletypes::SMALL_22_PP][6] = true;
    boundaryflags[tiletypes::SMALL_22_PP][7] = true;
    HELPER_SetBoundaryFlags_Perp(tiletypes::SMALL_22_PP,tiletypes::SMALL_67_NP);
    HELPER_SetBoundaryFlags_Perp(tiletypes::SMALL_67_NP,tiletypes::SMALL_22_NN);
    HELPER_SetBoundaryFlags_Perp(tiletypes::SMALL_22_NN,tiletypes::SMALL_67_PN);
    boundaryflags[tiletypes::SMALL_67_PP][0] = true;
    boundaryflags[tiletypes::SMALL_67_PP][1] = true;
    boundaryflags[tiletypes::SMALL_67_PP][6] = true;
    HELPER_SetBoundaryFlags_Perp(tiletypes::SMALL_67_PP,tiletypes::SMALL_22_NP);
    HELPER_SetBoundaryFlags_Perp(tiletypes::SMALL_22_NP,tiletypes::SMALL_67_NN);
    HELPER_SetBoundaryFlags_Perp(tiletypes::SMALL_67_NN,tiletypes::SMALL_22_PN);
    boundaryflags[tiletypes::LARGE_22_PP][0] = true;
    boundaryflags[tiletypes::LARGE_22_PP][1] = true;
    boundaryflags[tiletypes::LARGE_22_PP][4] = true;
    boundaryflags[tiletypes::LARGE_22_PP][6] = true;
    boundaryflags[tiletypes::LARGE_22_PP][7] = true;
    HELPER_SetBoundaryFlags_Perp(tiletypes::LARGE_22_PP,tiletypes::LARGE_67_NP);
    HELPER_SetBoundaryFlags_Perp(tiletypes::LARGE_67_NP,tiletypes::LARGE_22_NN);
    HELPER_SetBoundaryFlags_Perp(tiletypes::LARGE_22_NN,tiletypes::LARGE_67_PN);
    boundaryflags[tiletypes::LARGE_67_PP][0] = true;
    boundaryflags[tiletypes::LARGE_67_PP][1] = true;
    boundaryflags[tiletypes::LARGE_67_PP][2] = true;
    boundaryflags[tiletypes::LARGE_67_PP][6] = true;
    boundaryflags[tiletypes::LARGE_67_PP][7] = true;
    HELPER_SetBoundaryFlags_Perp(tiletypes::LARGE_67_PP,tiletypes::LARGE_22_NP);
    HELPER_SetBoundaryFlags_Perp(tiletypes::LARGE_22_NP,tiletypes::LARGE_67_NN);
    HELPER_SetBoundaryFlags_Perp(tiletypes::LARGE_67_NN,tiletypes::LARGE_22_PN);
    boundarydefs[0] = new TileEdgeArchetype_Linear(-1,-1,-1,0); //left bottom half  (-1,-1,-1, 0)
    boundarydefs[1] = new TileEdgeArchetype_Linear(-1,0,-1,1); //left top half      (-1, 0,-1, 1)
    boundarydefs[2] = new TileEdgeArchetype_Linear(-1,-1,-1,1); //left              (-1,-1,-1, 1)
    boundarydefs[9] = boundarydefs[1]->GeneratePerpArchetype(); //bottom left half  ( 0,-1,-1,-1)
    boundarydefs[10] = boundarydefs[0]->GeneratePerpArchetype(); //bottom right half( 1,-1, 0,-1)
    boundarydefs[11] = boundarydefs[2]->GeneratePerpArchetype(); //bottom           ( 1,-1,-1,-1)
    boundarydefs[7] = boundarydefs[10]->GeneratePerpArchetype(); //right top half   ( 1, 1, 1, 0)
    boundarydefs[6] = boundarydefs[9]->GeneratePerpArchetype(); //right bottom half ( 1, 0, 1,-1)
    boundarydefs[8] = boundarydefs[11]->GeneratePerpArchetype(); //right            ( 1, 1, 1,-1)
    boundarydefs[4] = boundarydefs[6]->GeneratePerpArchetype(); //top right half    ( 0, 1, 1, 1)
    boundarydefs[3] = boundarydefs[7]->GeneratePerpArchetype(); //top left half     (-1, 1, 0, 1)
    boundarydefs[5] = boundarydefs[8]->GeneratePerpArchetype(); //top               (-1, 1, 1, 1)
}

vector<Segment*> tiledefs::GenerateTileSegments_Filtered(int tileType, const vector<int>& neighborTiles, double xpos, double ypos, double halfWidth) {
    if (tileType < 0 || tileType >= tiletypes::num_tile_types) {
        return vector<Segment*>();
    }

    vector<Segment*> segments;
    for (int i = 0; i < 4; ++i) {
        bool collisionHalf1 = boundaryflags[tileType][i * 2] && !boundaryflags[neighborTiles[i]][(i * 2 + 4) % 8];
        bool collisionHalf2 = boundaryflags[tileType][i * 2 + 1] && !boundaryflags[neighborTiles[i]][(i * 2 + 1 + 4) % 8];

        if (collisionHalf1) {
            if (collisionHalf2) {
                segments.push_back(boundarydefs[i * 3 + 2]->GenerateCollisionSegment(xpos, ypos, halfWidth));
            } else {
                segments.push_back(boundarydefs[i * 3]->GenerateCollisionSegment(xpos, ypos, halfWidth));
            }
        } else if (collisionHalf2) {
            segments.push_back(boundarydefs[i * 3 + 1]->GenerateCollisionSegment(xpos, ypos, halfWidth));
        }
    }

    if (segdefs[tileType] != nullptr) {
        segments.push_back(segdefs[tileType]->GenerateCollisionSegment(xpos, ypos, halfWidth));
    }

    return segments;
}

vector<Segment*> tiledefs::GenerateTileSegments(int tileType, double xpos, double ypos, double halfWidth) {
    if (tileType < 0 || tileType >= tiletypes::num_tile_types) {
        return vector<Segment*>();
    }

    vector<Segment*> segments;
    for (int i = 0; i < 4; ++i) {
        bool collisionHalf1 = boundaryflags[tileType][i * 2];
        bool collisionHalf2 = boundaryflags[tileType][i * 2 + 1];

        if (collisionHalf1) {
            if (collisionHalf2) {
                segments.push_back(boundarydefs[i * 3 + 2]->GenerateCollisionSegment(xpos, ypos, halfWidth));
            } else {
                segments.push_back(boundarydefs[i * 3]->GenerateCollisionSegment(xpos, ypos, halfWidth));
            }
        } else if (collisionHalf2) {
            segments.push_back(boundarydefs[i * 3 + 1]->GenerateCollisionSegment(xpos, ypos, halfWidth));
        }
    }

    if (segdefs[tileType] != nullptr) {
        segments.push_back(segdefs[tileType]->GenerateCollisionSegment(xpos, ypos, halfWidth));
    }

    return segments;
}

void tiledefs::HELPER_InitBoundaryFlags() {
    for (int tileType = 0; tileType < tiletypes::num_tile_types; ++tileType) {
        boundaryflags[tileType] = vector<bool>(8, false);
    }
}

void tiledefs::HELPER_SetBoundaryFlags_Copy(int srcTileType, int destTileType) {
    for (int i = 0; i < 8; ++i) {
        boundaryflags[destTileType][i] = boundaryflags[srcTileType][i];
    }
}

void tiledefs::HELPER_SetBoundaryFlags_Perp(int srcTileType, int destTileType) {
    for (int i = 0; i < 8; ++i) {
        boundaryflags[destTileType][i] = boundaryflags[srcTileType][perpindex[i]];
    }
}