#pragma once
#include <vector>

#include "..\\editor\\Editor_State.h"
#include "..\\editor\\edat.h"
#include "..\\flash\\utils\\ByteArray.h"
#include "..\\math\\mathutils.h"
#include "..\\math\\vec2.h"
#include "..\\simpleFramework\\SimpleInput.h"
#include "collision\\Grid_Edges.h"
#include "collision\\Grid_Entity.h"
#include "collision\\Grid_Segment.h"
#include "collision\\Segment.h"
#include "collision\\Segment_Linear_DoubleSided.h"
#include "entities\\Entity_Base.h"
#include "entities\\Entity_BounceBlock.h"
#include "entities\\Entity_Door_Locked.h"
#include "entities\\Entity_Door_Regular.h"
#include "entities\\Entity_Door_Trap.h"
#include "entities\\Entity_Drone_Chaingun.h"
#include "entities\\Entity_Drone_Chaser.h"
#include "entities\\Entity_Drone_Laser.h"
#include "entities\\Entity_Drone_Zap.h"
#include "entities\\Entity_ExitDoor.h"
#include "entities\\Entity_ExitSwitch.h"
#include "entities\\Entity_FloorGuard.h"
#include "entities\\Entity_Gold.h"
#include "entities\\Entity_Launchpad.h"
#include "entities\\Entity_Mine.h"
#include "entities\\Entity_OnewayPlatform.h"
#include "entities\\Entity_Rocket.h"
#include "entities\\Entity_Thwomp.h"
#include "entities\\Entity_Turret.h"
#include "inputsource\\InputSource_Base.h"
#include "inputsource\\InputSource_Playback.h"
#include "inputsource\\InputSource_Recorder.h"
#include "ninja\\Ninja.h"
#include "..\\tiles\\tiledefs.h"
#include "..\\tiles\\tiletypes.h"

using namespace std;

class sim_loader {
    public:
        sim_loader() = delete;
        static Simulator* LoadLevel_EditorState(const vector<int>& playerKeys, const vector<unsigned int>& playerColors, SimpleInput& input, ByteArray* replayData, int playerCount, const Editor_State& editorState);
    private:
        static void LoadLevel_EditorState_Tiles(const vector<unsigned int>& tileIDs, vector<int>& tiles, Grid_Segment& gridSegment, Grid_Edges& gridEdges, int numCols, int numRows, double cellSize, double cellHalfWidth);
        static void LoadLevel_InitTileIDGridWithBoundaryEdges(vector<int>& tileIDGrid, int numCols, int numRows);
        static void LoadLevel_BuildTileSegs(Grid_Segment& gridSegment, double cellSize, double cellHalfWidth, int colIndex, int rowIndex, int tileType, const vector<int>& neighborTiles);
        static void LoadLevel_BuildTileEdges(Grid_Edges& gridEdges, int colIndex, int rowIndex, int tileType);
        static void LoadLevel_EditorState_Entities(const vector<vector<unsigned int>>& entityData, Grid_Segment& gridSegment, Grid_Edges& gridEdges, Grid_Entity& gridEntity, vector<Entity_Base*>& entities, vector<vec2>& ninjaSpawnLocations, double cellSize, double cellHalfWidth);
        static void Helper_RegisterEntity(vector<Entity_Base*>& entities, Entity_Base* entity);
        static unsigned int Helper_Editor_OldDirEnumToNewDirEnum(int oldDirEnum);
        static int Helper_Editor_NewDirEnumToOldDirEnum(unsigned int newDirEnum);
        static unsigned int Helper_Editor_VecToDirEnum(double x, double y);
    public:
        static Simulator* LoadFromSave(appSave& appState, const vector<int>& playerKeys, const vector<unsigned int>& playerColors, SimpleInput& input);
    private:
        static void LoadFromSave_Entities(vector<entitySave>& entityState, Grid_Segment& gridSegment, Grid_Edges& gridEdges, Grid_Entity& gridEntity, vector<Entity_Base*>& entities);
};
