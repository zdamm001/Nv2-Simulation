#include "sim_loader.h"

Simulator sim_loader::LoadLevel_EditorState(const vector<int>& playerKeys, const vector<unsigned int>& playerColors, const SimpleInput& input, const ByteArray& replayData, int playerCount, const Editor_State& editorState) {
    mathutils::GenerateNewRandomSeed();

    vector<int> tileIDGrid(Simulator::GRID_NUM_COLS * Simulator::GRID_NUM_ROWS, tiletypes::FULL);
    Grid_Segment gridSegment(Simulator::GRID_NUM_COLS, Simulator::GRID_NUM_ROWS, Simulator::GRID_CELL_SIZE);
    Grid_Edges gridEdges(Simulator::GRID_NUM_COLS * 2, Simulator::GRID_NUM_ROWS * 2, Simulator::GRID_CELL_SIZE * 0.5);
    Grid_Entity gridEntity(Simulator::GRID_NUM_COLS, Simulator::GRID_NUM_ROWS, Simulator::GRID_CELL_SIZE);

    vector<Entity_Base*> entities;
    vector<vec2> ninjaSpawnLocations;

    LoadLevel_EditorState_Tiles(editorState.tileIDs, tileIDGrid, gridSegment, gridEdges, Simulator::GRID_NUM_COLS, Simulator::GRID_NUM_ROWS, Simulator::GRID_CELL_SIZE, Simulator::GRID_CELL_HALFWIDTH);

    LoadLevel_EditorState_Entities(editorState.entities, gridSegment, gridEdges, gridEntity, entities, ninjaSpawnLocations, Simulator::GRID_CELL_SIZE, Simulator::GRID_CELL_HALFWIDTH);

    if (ninjaSpawnLocations.empty()) {
        ninjaSpawnLocations.push_back(vec2(32, 32));
    }

    while (ninjaSpawnLocations.size() < playerCount) {
        ninjaSpawnLocations.push_back(ninjaSpawnLocations[0]);
    }

    if (ninjaSpawnLocations.size() == 2) {
        ninjaSpawnLocations[0].x -= 4;
        ninjaSpawnLocations[1].x += 4;
    }

    vector<Ninja> ninjas(ninjaSpawnLocations.size());

    for (size_t i = 0; i < ninjaSpawnLocations.size(); ++i) {
        InputSource_Base* inputSource = nullptr;
        
        if (replayData.IsEmpty()) {
            inputSource = new InputSource_Recorder(input, playerKeys[i * 3 % playerKeys.size()], playerKeys[(i * 3 + 1) % playerKeys.size()], playerKeys[(i * 3 + 2) % playerKeys.size()]);
        } else {
            inputSource = new InputSource_Playback(replayData);
        }
        
        ninjas[i] = Ninja(i, inputSource, ninjaSpawnLocations[i].x, ninjaSpawnLocations[i].y, playerColors[i]);
    }

    return Simulator(tileIDGrid, gridSegment, gridEdges, gridEntity, entities, ninjas);
}