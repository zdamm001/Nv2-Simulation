#pragma once
#include <vector>

#include "..\\..\\tiles\\edgedefs.h"
#include "..\\..\\tiles\\edgetypes.h"
#include "Grid_Base.h"

class SimpleRenderer;

class Grid_Edges : public Grid_Base {
    private:
        vector<int> edges_tileX;
        vector<int> edges_tileY;
        vector<int> edges_doorX;
        vector<int> edges_doorY;
    public:
        Grid_Edges(int num_cols, int num_rows, double cell_size);
        Grid_Edges(int num_cols, int num_rows, double cell_size, vector<int> edgesTileX, vector<int> edgesTileY, vector<int> edgesDoorX, vector<int> edgesDoorY);
        void Clear();
        void Debug_Draw(SimpleRenderer& rend);
        int DOOR_GetCellIndexFromGridspacePosition(int u, int v);
        int GetGridCoordinateFromWorldspace_1D(double world_coord);
        int GetWorldspaceCoordinateFromGridEdge_1D(int grid_coord, int dir);
        bool IsSolid(int u, int v, int dir_u, int dir_v);
        bool IsSolid_IgnoreDoors(int u, int v, int dir_u, int dir_v);
        bool IsEmpty(int u, int v, int dir_u, int dir_v);
        bool ScanHorizontal(int min_v, int max_v, int start_u, int end_u);
        bool ScanHorizontal_Directed(int min_v, int max_v, int start_u, int end_u, int dir_u);
        bool ScanVertical(int min_u, int max_u, int start_v, int end_v);
        bool ScanVertical_Directed(int min_u, int max_u, int start_v, int end_v, int dir_v);
        int SweepHorizontal(int min_v, int max_v, int start_u, int dir);
        int SweepVertical(int min_u, int max_u, int start_v, int dir);
        bool IsEmpty_Column(int u, int min_v, int max_v, int dir);
        bool IsEmpty_Row(int v, int min_u, int max_u, int dir);
        void GAME_LoadTileEdges(int tile_u, int tile_v, int tileID);
        void DOOR_IncrementEdge(int cell_index, bool isHorizontal);
        void DOOR_DecrementEdge(int cell_index, bool isHorizontal);
    private:
        int GetIndexFromGridspaceAndOffset(int u, int v, int dir_u, int dir_v);
        void LoadEdgeState_X(int index, int edgestate);
        void LoadEdgeState_Y(int index, int edgestate);
        void SetDoorState_X(int index, int edgestate);
        void SetDoorState_Y(int index, int edgestate);
    public:
        Grid_Edges* Clone() const;
};