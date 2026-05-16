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
    private:
        static const char OLDDATA_SEPERATION_CHAR_LEVEL = '|';
        static const char OLDDATA_SEPERATION_CHAR_OBJECT = '!';
        static const char OLDDATA_SEPERATION_CHAR_OBJTYPE = '^';
        static const char OLDDATA_SEPERATION_CHAR_OBJPARAM = ',';
        static const int OLDDATA_CHAR_PAD = 48;
        static const int OLDDATA_OBJTYPE_GOLD = 0;
        static const int OLDDATA_OBJTYPE_BOUNCEBLOCK = 1;
        static const int OLDDATA_OBJTYPE_LAUNCHPAD = 2;
        static const int OLDDATA_OBJTYPE_TURRET = 3;
        static const int OLDDATA_OBJTYPE_FLOORGUARD = 4;
        static const int OLDDATA_OBJTYPE_PLAYER = 5;
        static const int OLDDATA_OBJTYPE_DRONE = 6;
        static const int OLDDATA_OBJTYPE_ONEWAYPLATFORM = 7;
        static const int OLDDATA_OBJTYPE_THWOMP = 8;
        static const int OLDDATA_OBJTYPE_TESTDOOR = 9;
        static const int OLDDATA_OBJTYPE_HOMINGLAUNCHER = 10;
        static const int OLDDATA_OBJTYPE_EXIT = 11;
        static const int OLDDATA_OBJTYPE_MINE = 12;
    public:
        sim_loader() = delete;
        static Simulator* LoadLevel_EditorState(const vector<int>& playerKeys, const vector<unsigned int>& playerColors, SimpleInput& input, ByteArray* replayData, int playerCount, const Editor_State& editorState);
    private:
        static void LoadLevel_EditorState_Tiles(const vector<unsigned int>& tileIDs, vector<int>& tiles, Grid_Segment* gridSegment, Grid_Edges* gridEdges, int numCols, int numRows, double cellSize, double cellHalfWidth);
        static void LoadLevel_InitTileIDGridWithBoundaryEdges(vector<int>& tileIDGrid, int numCols, int numRows);
        static void LoadLevel_BuildTileSegs(Grid_Segment* gridSegment, double cellSize, double cellHalfWidth, int colIndex, int rowIndex, int tileType, const vector<int>& neighborTiles);
        static void LoadLevel_BuildTileEdges(Grid_Edges* gridEdges, int colIndex, int rowIndex, int tileType);
        static void LoadLevel_EditorState_Entities(const vector<vector<unsigned int>>& entityData, Grid_Segment* gridSegment, Grid_Edges* gridEdges, Grid_Entity* gridEntity, vector<Entity_Base*>& entities, vector<vec2>& ninjaSpawnLocations, double cellSize, double cellHalfWidth);
        static void Helper_RegisterEntity(vector<Entity_Base*>& entities, Entity_Base* entity);
        static vec2 HELPER_OldData_UnpackDirEnum(double num);
    public:
        static Editor_State* BuildEditorState_OldData(const string& data);
    private:
        static void BuildEditorState_OldData_Tiles(const string& data, vector<unsigned int> tileIDs, int offset);
        static void BuildEditorState_OldData_Entities(const string& data, vector<vector<unsigned int>>& entities, int offset);
        static void BuildEditorState_OldData_CreateEntity(int type, const vector<double>& props, vector<vector<unsigned int>>& entities, int offset);
        static unsigned int Helper_Editor_GetQuantizedPosition(double value);
        static unsigned int Helper_Editor_OldDirEnumToNewDirEnum(int oldDirEnum);
        static int Helper_Editor_NewDirEnumToOldDirEnum(unsigned int newDirEnum);
        static unsigned int Helper_Editor_VecToDirEnum(double x, double y);
    public:
        static Simulator* LoadFromSave(appSave& appState, const vector<int>& playerKeys, const vector<unsigned int>& playerColors, SimpleInput& input);
    private:
        static void LoadFromSave_Entities(vector<entitySave>& entityState, Grid_Segment* gridSegment, Grid_Edges* gridEdges, Grid_Entity* gridEntity, vector<Entity_Base*>& entities);
};
