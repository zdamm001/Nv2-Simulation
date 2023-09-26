#pragma once
#include <vector>

#include "..\\simulation\\collision\\Segment.h"
#include "tiletypes.h"
#include "TileEdgeArchetype.h"
#include "TileEdgeArchetype_Circular.h"
#include "TileEdgeArchetype_Linear.h"

using namespace std;

class tiledefs {
    private:
        static vector<TileEdgeArchetype*> segdefs;
        static vector<unsigned int> perpindex;
        static vector<vector<bool>> boundaryflags;
        static vector<TileEdgeArchetype*> boundarydefs;
    public:
        tiledefs() = delete;
        static void Initialize();
        static vector<Segment*> GenerateTileSegments_Filtered(int tileType, const vector<int>& neighborTiles, double xpos, double ypos, double halfWidth);
        static vector<Segment*> GenerateTileSegments(int tileType, double xpos, double ypos, double halfWidth);
    private:
        static void HELPER_InitBoundaryFlags();
        static void HELPER_SetBoundaryFlags_Copy(int srcTileType, int destTileType);
        static void HELPER_SetBoundaryFlags_Perp(int srcTileType, int destTileType);
};