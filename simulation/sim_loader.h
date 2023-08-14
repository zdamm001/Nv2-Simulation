#pragma once
#include <vector>

#include "..\\editor\\edat.h"
#include "..\\flash\\utils\\ByteArray.h"
#include "..\\math\\mathutils.h"
#include "..\\math\\vec2.h"

#include "collision\\Grid_Edges.h"
#include "collision\\Grid_Entity.h"
#include "collision\\Grid_Segment.h"
#include "collision\\Segment.h"
//#include "collision\\Segment_Linear_DoubleSided.h"
#include "entities\\Entity_Base.h"
//#include "entities\\Entity_ExitDoor.h"
//#include "entities\\Entity_ExitSwitch.h"
#include "ninja\\Ninja.h"
//#include "..\\tiles\\tiledefs.h"
#include "..\\tiles\\tiletypes.h"

using namespace std;

class Editor_State;
class SimpleInput;
class InputSource_Base;

class sim_loader {
    public:
        sim_loader() = delete;
        Simulator LoadLevel_EditorState(const vector<int>& playerKeys, const vector<unsigned int>& playerColors, const SimpleInput& input, const ByteArray& replayData, int playerCount, const Editor_State& editorState);
};
