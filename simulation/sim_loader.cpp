#include "sim_loader.h"

Simulator* sim_loader::LoadLevel_EditorState(const vector<int>& playerKeys, const vector<unsigned int>& playerColors, SimpleInput& input, ByteArray* replayData, int playerCount, const Editor_State& editorState) {
    mathutils::GenerateNewRandomSeed();

    vector<int> tileIDGrid(Simulator::GRID_NUM_COLS * Simulator::GRID_NUM_ROWS, tiletypes::FULL);
    Grid_Segment* gridSegment = new Grid_Segment(Simulator::GRID_NUM_COLS, Simulator::GRID_NUM_ROWS, Simulator::GRID_CELL_SIZE);
    Grid_Edges* gridEdges = new Grid_Edges(Simulator::GRID_NUM_COLS * 2, Simulator::GRID_NUM_ROWS * 2, Simulator::GRID_CELL_SIZE * 0.5);
    Grid_Entity* gridEntity = new Grid_Entity(Simulator::GRID_NUM_COLS, Simulator::GRID_NUM_ROWS, Simulator::GRID_CELL_SIZE);

    vector<Entity_Base*> entities;
    vector<vec2> ninjaSpawnLocations;

    LoadLevel_EditorState_Tiles(editorState.tileIDs, tileIDGrid, gridSegment, gridEdges, Simulator::GRID_NUM_COLS, Simulator::GRID_NUM_ROWS, Simulator::GRID_CELL_SIZE, Simulator::GRID_CELL_HALFWIDTH);

    LoadLevel_EditorState_Entities(editorState.entities, gridSegment, gridEdges, gridEntity, entities, ninjaSpawnLocations, Simulator::GRID_CELL_SIZE, Simulator::GRID_CELL_HALFWIDTH);

    if (ninjaSpawnLocations.empty()) {
        ninjaSpawnLocations.push_back(vec2(32, 32));
    }

    while (int(ninjaSpawnLocations.size()) < playerCount) {
        ninjaSpawnLocations.push_back(ninjaSpawnLocations[0]);
    }

    if (ninjaSpawnLocations.size() == 2) {
        ninjaSpawnLocations[0].x -= 4;
        ninjaSpawnLocations[1].x += 4;
    }

    vector<Ninja*> ninjas(ninjaSpawnLocations.size());

    for (size_t i = 0; i < ninjaSpawnLocations.size(); ++i) {
        InputSource_Base* inputSource = nullptr;
        
        if (replayData == nullptr) {
            inputSource = new InputSource_Recorder(input, playerKeys[i * 3 % playerKeys.size()], playerKeys[(i * 3 + 1) % playerKeys.size()], playerKeys[(i * 3 + 2) % playerKeys.size()]);
        } else {
            inputSource = new InputSource_Playback(replayData);
        }
        
        ninjas[i] = new Ninja(i, inputSource, ninjaSpawnLocations[i].x, ninjaSpawnLocations[i].y, playerColors[i]);
    }

    return new Simulator(tileIDGrid, gridSegment, gridEdges, gridEntity, entities, ninjas);
}

void sim_loader::LoadLevel_EditorState_Tiles(const vector<unsigned int>& tileIDs, vector<int>& tileIDGrid, Grid_Segment* gridSegment, Grid_Edges* gridEdges, int numCols, int numRows, double cellSize, double cellHalfWidth) {
    gridSegment->Clear();
    gridEdges->Clear();
    LoadLevel_InitTileIDGridWithBoundaryEdges(tileIDGrid, numCols, numRows);

    for (size_t i = 0; i < tileIDs.size(); ++i) {
        int colIndex = 1 + i % edat::num_cols;
        int rowIndex = 1 + i / edat::num_cols;
        tileIDGrid[colIndex + rowIndex * numCols] = tileIDs[i];
    }

    vector<int> neighborTiles(4, tiletypes::EMPTY);
    for (size_t gridIndex = 0; gridIndex < tileIDGrid.size(); ++gridIndex) {
        int col = gridIndex % numCols;
        int row = gridIndex / numCols;

        if (col == 0) {
            neighborTiles[0] = tiletypes::EMPTY;
        } else {
            neighborTiles[0] = tileIDGrid[col - 1 + row * numCols];
        }

        if (col == numCols - 1) {
            neighborTiles[2] = tiletypes::EMPTY;
        } else {
            neighborTiles[2] = tileIDGrid[col + 1 + row * numCols];
        }

        if (row == 0) {
            neighborTiles[3] = tiletypes::EMPTY;
        } else {
            neighborTiles[3] = tileIDGrid[col + (row - 1) * numCols];
        }

        if (row == numRows - 1) {
            neighborTiles[1] = tiletypes::EMPTY;
        } else {
            neighborTiles[1] = tileIDGrid[col + (row + 1) * numCols];
        }

        LoadLevel_BuildTileSegs(gridSegment, cellSize, cellHalfWidth, col, row, tileIDGrid[gridIndex], neighborTiles);
        LoadLevel_BuildTileEdges(gridEdges, col, row, tileIDGrid[gridIndex]);
    }
}

void sim_loader::LoadLevel_InitTileIDGridWithBoundaryEdges(vector<int>& tileIDGrid, int numCols, int numRows) {
    int numCells = numCols * numRows;

    for (int i = 0; i < numCells; ++i) {
        tileIDGrid[i] = tiletypes::EMPTY;
    }

    for (int col = 1; col < numCols - 1; ++col) {
        tileIDGrid[col] = tiletypes::EDGE_BOTTOM;
        tileIDGrid[col + (numRows - 1) * numCols] = tiletypes::EDGE_TOP;
    }

    for (int row = 1; row < numRows - 1; ++row) {
        tileIDGrid[row * numCols] = tiletypes::EDGE_RIGHT;
        tileIDGrid[row * numCols + numCols - 1] = tiletypes::EDGE_LEFT;
    }

    tileIDGrid[0] = tiletypes::EDGE_CORNER_UL;
    tileIDGrid[numCols - 1] = tiletypes::EDGE_CORNER_UR;
    tileIDGrid[(numRows - 1) * numCols] = tiletypes::EDGE_CORNER_DL;
    tileIDGrid[numCols * numRows - 1] = tiletypes::EDGE_CORNER_DR;
}

void sim_loader::LoadLevel_BuildTileSegs(Grid_Segment* gridSegment, double cellSize, double cellHalfWidth, int colIndex, int rowIndex, int tileType, const vector<int>& neighborTiles) {
    vector<Segment*> segments = tiledefs::GenerateTileSegments_Filtered(tileType, neighborTiles, colIndex * cellSize + cellHalfWidth, rowIndex * cellSize + cellHalfWidth, cellHalfWidth);
    
    for (size_t i = 0; i < segments.size(); ++i) {
        gridSegment->AddSegToCell(colIndex, rowIndex, segments[i]);
    }
}

void sim_loader::LoadLevel_BuildTileEdges(Grid_Edges* gridEdges, int colIndex, int rowIndex, int tileType) {
    gridEdges->GAME_LoadTileEdges(colIndex, rowIndex, tileType);
}

void sim_loader::LoadLevel_EditorState_Entities(const vector<vector<unsigned int>>& entityData, Grid_Segment* gridSegment, Grid_Edges* gridEdges, Grid_Entity* gridEntity, vector<Entity_Base*>& entities, vector<vec2>& ninjaSpawnLocations, double cellSize, double cellHalfWidth) {
    unsigned int entityType;
    double entityX;
    double entityY;
    unsigned int entityDir;
    unsigned int entityMove;

    gridEntity->Clear();
    entities.clear();
    ninjaSpawnLocations.clear();

    for (size_t i = 0; i < entityData.size(); ++i) {
        const vector<unsigned int>& entityProps = entityData[i];
        entityType = entityProps[edat::EPROP_TYPE];
        entityX = entityProps[edat::EPROP_X] * edat::quantize_step_size;
        entityY = entityProps[edat::EPROP_Y] * edat::quantize_step_size;
        entityDir = 0;
        entityMove = 0;

        if (entityProps.size() > 3) {
            entityDir = entityProps[edat::EPROP_DIR];
            if (entityProps.size() > 4) {
                entityMove = entityProps[edat::EPROP_MOVE];
            }
        }

        if (entityType == edat::ETYPE_BOUNCEBLOCK) {
            Entity_BounceBlock* bounceBlock = new Entity_BounceBlock(gridEntity, entityX, entityY);
            Helper_RegisterEntity(entities, bounceBlock);
        }
        else if (entityType == edat::ETYPE_CHAINGUN) {
            Entity_Drone_Chaingun* chaingunDrone = new Entity_Drone_Chaingun(gridEntity, entityX, entityY, Helper_Editor_NewDirEnumToOldDirEnum(entityDir), entityMove);
            Helper_RegisterEntity(entities, chaingunDrone);
        }
        else if (entityType == edat::ETYPE_CHASER) {
            Entity_Drone_Chaser* chaserDrone = new Entity_Drone_Chaser(gridEntity, entityX, entityY, Helper_Editor_NewDirEnumToOldDirEnum(entityDir), entityMove);
            Helper_RegisterEntity(entities, chaserDrone);
        }
        else if (entityType == edat::ETYPE_DOOR_LOCKED || entityType == edat::ETYPE_DOOR_REGULAR || entityType == edat::ETYPE_DOOR_TRAP) {
            vec2 directionVector = edat::MAP_DIR_TO_VEC(entityDir);
            int gridX = static_cast<int>(floor((entityX - directionVector.x * 12) / 24));
            int gridY = static_cast<int>(floor((entityY - directionVector.y * 12) / 24));
            int cellIndex = gridSegment->DOOR_GetCellIndexFromGridspacePosition(gridX, gridY);
            bool isVertical = (entityDir == 0);
            vector<int> edgeCells(2, 0);

            if (!isVertical) {
                edgeCells[0] = gridEdges->DOOR_GetCellIndexFromGridspacePosition(gridX * 2, gridY * 2 + 1);
                edgeCells[1] = gridEdges->DOOR_GetCellIndexFromGridspacePosition(gridX * 2 + 1, gridY * 2 + 1);
            } else {
                edgeCells[0] = gridEdges->DOOR_GetCellIndexFromGridspacePosition(gridX * 2 + 1, gridY * 2);
                edgeCells[1] = gridEdges->DOOR_GetCellIndexFromGridspacePosition(gridX * 2 + 1, gridY * 2 + 1);
            }

            vec2 cellCenterPosition = gridSegment->DEBUG_GetWorldspaceCellCenterPositionFromIndex(cellIndex);
            vec2 entityPosition(entityX, entityY);
            vec2 perpendicularVector = directionVector.Perp();
            perpendicularVector.Scale(12);
            vec2 sideA = entityPosition.Plus(perpendicularVector);
            vec2 sideB = entityPosition.Minus(perpendicularVector);
            Segment_Linear_DoubleSided* doorSegment = new Segment_Linear_DoubleSided(sideA.x, sideA.y, sideB.x, sideB.y);

            if (entityType == edat::ETYPE_DOOR_REGULAR) {
                Entity_Door_Regular* regularDoor = new Entity_Door_Regular(gridEntity, gridSegment, cellIndex, doorSegment, gridEdges, edgeCells, isVertical, entityX, entityY);
                Helper_RegisterEntity(entities, regularDoor);
            } else {
                vector<unsigned int> nextEntityData = entityData[i + 1];
                unsigned int nextEntityX = nextEntityData[edat::EPROP_X] * edat::quantize_step_size;
                unsigned int nextEntityY = nextEntityData[edat::EPROP_Y] * edat::quantize_step_size;

                if (entityType == edat::ETYPE_DOOR_LOCKED) {
                    Entity_Door_Locked* lockedDoor = new Entity_Door_Locked(gridEntity, gridSegment, cellIndex, doorSegment, gridEdges, edgeCells, isVertical, nextEntityX, nextEntityY);
                    Helper_RegisterEntity(entities, lockedDoor);
                }
                else if (entityType == edat::ETYPE_DOOR_TRAP) {
                    Entity_Door_Trap* trapDoor = new Entity_Door_Trap(gridEntity, gridSegment, cellIndex, doorSegment, gridEdges, edgeCells, isVertical, nextEntityX, nextEntityY);
                    Helper_RegisterEntity(entities, trapDoor);
                }
            }
        }
        else if (entityType == edat::ETYPE_EXIT_DOOR) {
            Entity_ExitDoor* exitDoor = new Entity_ExitDoor(entityX, entityY);
            Helper_RegisterEntity(entities, exitDoor);

            vector<unsigned int> nextEntityData = entityData[i + 1];
            unsigned int nextEntityX = nextEntityData[edat::EPROP_X] * edat::quantize_step_size;
            unsigned int nextEntityY = nextEntityData[edat::EPROP_Y] * edat::quantize_step_size;

            Entity_ExitSwitch* exitSwitch = new Entity_ExitSwitch(gridEntity, nextEntityX, nextEntityY, exitDoor);
            Helper_RegisterEntity(entities, exitSwitch);
        }
        else if (entityType == edat::ETYPE_EXIT_SWITCH) {
            if (i > 0) {
                if (entityData[i - 1][edat::EPROP_TYPE] == edat::ETYPE_EXIT_DOOR) {
                    continue;
                }
            }
        }
        else if (entityType == edat::ETYPE_FLOORGUARD) {
            Entity_FloorGuard* floorGuard = new Entity_FloorGuard(gridEntity, entityX, entityY);
            Helper_RegisterEntity(entities, floorGuard);
        }
        else if (entityType == edat::ETYPE_GOLD) {
            Entity_Gold* gold = new Entity_Gold(gridEntity, entityX, entityY);
            Helper_RegisterEntity(entities, gold);
        }
        else if (entityType == edat::ETYPE_LASER) {
            Entity_Drone_Laser* laserDrone = new Entity_Drone_Laser(gridEntity, entityX, entityY, Helper_Editor_NewDirEnumToOldDirEnum(entityDir), entityMove);
            Helper_RegisterEntity(entities, laserDrone);
        }
        else if (entityType == edat::ETYPE_LAUNCHPAD) {
            vec2 directionVector = edat::MAP_DIR_TO_VEC(entityDir);
            Entity_Launchpad* launchpad = new Entity_Launchpad(gridEntity, entityX, entityY, directionVector.x, directionVector.y);
            Helper_RegisterEntity(entities, launchpad);
        }
        else if (entityType == edat::ETYPE_MINE) {
            Entity_Mine* mine = new Entity_Mine(gridEntity, entityX, entityY);
            Helper_RegisterEntity(entities, mine);
        }
        else if (entityType == edat::ETYPE_ONEWAY) {
            vec2 directionVector = edat::MAP_DIR_TO_VEC(entityDir);
            Entity_OnewayPlatform* onewayPlatform = new Entity_OnewayPlatform(gridEntity, entityX, entityY, directionVector.x, directionVector.y);
            Helper_RegisterEntity(entities, onewayPlatform);
        }
        else if (entityType == edat::ETYPE_PLAYER) {
            ninjaSpawnLocations.push_back(vec2(entityX, entityY));
        }
        else if (entityType == edat::ETYPE_ROCKET) {
            Entity_Rocket* rocket = new Entity_Rocket(gridEntity, entityX, entityY);
            Helper_RegisterEntity(entities, rocket);
        }
        else if (entityType == edat::ETYPE_SWITCH_LOCKED) {
            if (i > 0) {
                if (entityData[i - 1][edat::EPROP_TYPE] == edat::ETYPE_DOOR_LOCKED) {
                    continue;
                }
            }
        }
        else if (entityType == edat::ETYPE_SWITCH_TRAP) {
            if (i > 0) {
                if (entityData[i - 1][edat::EPROP_TYPE] == edat::ETYPE_DOOR_TRAP) {
                    continue;
                }
            }
        }
        else if (entityType == edat::ETYPE_THWOMP) {
            vec2 directionVector = edat::MAP_DIR_TO_VEC(entityDir);
            double fallDirection = 0;
            bool isHorizontal = false;

            if (directionVector.y == 0) {
                fallDirection = directionVector.x;
                isHorizontal = true;
            } else {
                fallDirection = directionVector.y;
            }

            Entity_Thwomp* thwomp = new Entity_Thwomp(gridEntity, entityX, entityY, fallDirection, isHorizontal);
            Helper_RegisterEntity(entities, thwomp);
        }
        else if (entityType == edat::ETYPE_TURRET) {
            Entity_Turret* turret = new Entity_Turret(gridEntity, entityX, entityY);
            Helper_RegisterEntity(entities, turret);
        }
        else if (entityType == edat::ETYPE_ZAP) {
            Entity_Drone_Zap* zapDrone = new Entity_Drone_Zap(gridEntity, entityX, entityY, Helper_Editor_NewDirEnumToOldDirEnum(entityDir), entityMove);
            Helper_RegisterEntity(entities, zapDrone);
        }
    }
}

void sim_loader::Helper_RegisterEntity(vector<Entity_Base*>& entities, Entity_Base* entity) {
    entity->GAME_SetUID(entities.size());
    entities.push_back(entity);
}

vec2 sim_loader::HELPER_OldData_UnpackDirEnum(double num) {
    if (num == 0) {
        return vec2(1, 0);
    }
    if (num == 1) {
        return vec2(0, 1);
    }
    if (num == 2) {
        return vec2(-1, 0);
    }
    if (num == 3) {
        return vec2(0, -1);
    }
    return vec2(0, 0);
}

vector<string> split(string str, char delimiter) {
    vector<string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }
    tokens.push_back(str.substr(start));
    return tokens;
}

Editor_State* sim_loader::BuildEditorState_OldData(const string& data) {
    Editor_State* state = new Editor_State();
    int tileOffset = 0;
    int entityOffset = 0;
    if (edat::num_cols != 31) {
        tileOffset = 5;
        entityOffset = tileOffset * edat::quantize_steps_per_cell;
    }
    vector<string> parts = split(data, OLDDATA_SEPERATION_CHAR_LEVEL);
    if (!parts.empty()) {
        BuildEditorState_OldData_Tiles(parts[0], state->tileIDs, tileOffset);
    }
    if (parts.size() > 1) {
        BuildEditorState_OldData_Entities(parts[1], state->entities, entityOffset);
    }
    return state;
}

void sim_loader::BuildEditorState_OldData_Tiles(const string& data, vector<unsigned int> tileIDs, int offset) {
    if (data.length() != 31 * 23) {
        return;
    }
    for (size_t i = 0; i < tileIDs.size(); i++) {
        tileIDs[i] = tiletypes::FULL;
    }
    for (size_t i = 0; i < data.length(); i++) {
        int row = static_cast<int>(i % edat::num_rows);
        int col = static_cast<int>(i / edat::num_rows);
        char c = data[i];
        int value = static_cast<int>(c) - OLDDATA_CHAR_PAD;
        tileIDs[col + row * edat::num_cols + offset] = tiletypes::GetTypeFromChar(value);
    }
}

void sim_loader::BuildEditorState_OldData_Entities(const string& data, vector<vector<unsigned int>>& entities, int offset = 0) {
    if (data.empty()) {
        return;
    }
    vector<string> objectList = split(data, OLDDATA_SEPERATION_CHAR_OBJECT);
    for (const string& objectStr : objectList) {
        vector<string> typeSplit = split(objectStr, OLDDATA_SEPERATION_CHAR_OBJTYPE);
        if (typeSplit.size() < 2) {
            continue;
        }
        int type = stoi(typeSplit[0]);
        vector<string> propsSplit = split(typeSplit[1], OLDDATA_SEPERATION_CHAR_OBJPARAM);
        vector<double> props(propsSplit.size());
        for (size_t i = 0; i < propsSplit.size(); i++) {
            props[i] = stod(propsSplit[i]);
        }
        BuildEditorState_OldData_CreateEntity(type, props, entities, offset);
    }
}

void sim_loader::BuildEditorState_OldData_CreateEntity(int type, const vector<double>& props, vector<vector<unsigned int>>& entities, int offset = 0) {
    if (type == OLDDATA_OBJTYPE_BOUNCEBLOCK) {
        if (props.size() == 2) {
            vector<unsigned int> e(3);
            e[edat::EPROP_TYPE] = edat::ETYPE_BOUNCEBLOCK;
            e[edat::EPROP_X] = Helper_Editor_GetQuantizedPosition(props[0]) + offset;
            e[edat::EPROP_Y] = Helper_Editor_GetQuantizedPosition(props[1]);
            entities.push_back(e);
        }
    }
    else if (type == OLDDATA_OBJTYPE_GOLD) {
        if (props.size() == 2) {
            vector<unsigned int> e(3);
            e[edat::EPROP_TYPE] = edat::ETYPE_GOLD;
            e[edat::EPROP_X] = Helper_Editor_GetQuantizedPosition(props[0]) + offset;
            e[edat::EPROP_Y] = Helper_Editor_GetQuantizedPosition(props[1]);
            entities.push_back(e);
        }
    }
    else if (type == OLDDATA_OBJTYPE_LAUNCHPAD) {
        if (props.size() == 4) {
            vector<unsigned int> e(4);
            e[edat::EPROP_TYPE] = edat::ETYPE_LAUNCHPAD;
            e[edat::EPROP_X] = Helper_Editor_GetQuantizedPosition(props[0]) + offset;
            e[edat::EPROP_Y] = Helper_Editor_GetQuantizedPosition(props[1]);
            e[edat::EPROP_DIR] = Helper_Editor_VecToDirEnum(props[2], props[3]);
            entities.push_back(e);
        }
    }
    else if (type == OLDDATA_OBJTYPE_MINE) {
        if (props.size() == 2) {
            vector<unsigned int> e(3);
            e[edat::EPROP_TYPE] = edat::ETYPE_MINE;
            e[edat::EPROP_X] = Helper_Editor_GetQuantizedPosition(props[0]) + offset;
            e[edat::EPROP_Y] = Helper_Editor_GetQuantizedPosition(props[1]);
            entities.push_back(e);
        }
    }
    else if (type == OLDDATA_OBJTYPE_ONEWAYPLATFORM) {
        if (props.size() == 3) {
            vec2 dir = HELPER_OldData_UnpackDirEnum(props[2]);
            vector<unsigned int> e(4);
            e[edat::EPROP_TYPE] = edat::ETYPE_ONEWAY;
            e[edat::EPROP_X] = Helper_Editor_GetQuantizedPosition(props[0] + 12 * dir.x) + offset;
            e[edat::EPROP_Y] = Helper_Editor_GetQuantizedPosition(props[1] + 12 * dir.y);
            e[edat::EPROP_DIR] = Helper_Editor_OldDirEnumToNewDirEnum(props[2]);
            entities.push_back(e);
        }
    }
    else if (type == OLDDATA_OBJTYPE_DRONE) {
        if (props.size() == 6) {
            vector<unsigned int> e(5);
            if (props[3]) {
                e[edat::EPROP_TYPE] = edat::ETYPE_CHASER;
            }
            else if (props[4] == 0) {
                e[edat::EPROP_TYPE] = edat::ETYPE_ZAP;
            }
            else if (props[4] == 1) {
                e[edat::EPROP_TYPE] = edat::ETYPE_LASER;
            }
            else if (props[4] == 2) {
                e[edat::EPROP_TYPE] = edat::ETYPE_CHAINGUN;
            }
            else {
                return;
            }
            e[edat::EPROP_X] = Helper_Editor_GetQuantizedPosition(props[0]) + offset;
            e[edat::EPROP_Y] = Helper_Editor_GetQuantizedPosition(props[1]);
            e[edat::EPROP_DIR] = Helper_Editor_OldDirEnumToNewDirEnum(props[5]);
            e[edat::EPROP_MOVE] = min(3u, static_cast<unsigned int>(props[2]));
            entities.push_back(e);
        }
    }
    else if (type == OLDDATA_OBJTYPE_EXIT) {
        if (props.size() == 4) {
            vector<unsigned int> door(3);
            door[edat::EPROP_TYPE] = edat::ETYPE_EXIT_DOOR;
            door[edat::EPROP_X] = Helper_Editor_GetQuantizedPosition(props[0]) + offset;
            door[edat::EPROP_Y] = Helper_Editor_GetQuantizedPosition(props[1]);
            entities.push_back(door);
            vector<unsigned int> sw(3);
            sw[edat::EPROP_TYPE] = edat::ETYPE_EXIT_SWITCH;
            sw[edat::EPROP_X] = Helper_Editor_GetQuantizedPosition(props[2]) + offset;
            sw[edat::EPROP_Y] = Helper_Editor_GetQuantizedPosition(props[3]);
            entities.push_back(sw);
        }
    }
    else if (type == OLDDATA_OBJTYPE_FLOORGUARD) {
        if (props.size() == 3) {
            vector<unsigned int> e(3);
            e[edat::EPROP_TYPE] = edat::ETYPE_FLOORGUARD;
            e[edat::EPROP_X] = Helper_Editor_GetQuantizedPosition(props[0]) + offset;
            e[edat::EPROP_Y] = Helper_Editor_GetQuantizedPosition(props[1]);
            entities.push_back(e);
        }
    }
    else if (type == OLDDATA_OBJTYPE_HOMINGLAUNCHER) {
        if (props.size() == 2) {
            vector<unsigned int> e(3);
            e[edat::EPROP_TYPE] = edat::ETYPE_ROCKET;
            e[edat::EPROP_X] = Helper_Editor_GetQuantizedPosition(props[0]) + offset;
            e[edat::EPROP_Y] = Helper_Editor_GetQuantizedPosition(props[1]);
            entities.push_back(e);
        }
    }
    else if (type == OLDDATA_OBJTYPE_TESTDOOR) {
        if (props.size() == 9) {
            int x = static_cast<int>(props[4] + props[7]);
            int y = static_cast<int>(props[5] + props[8]);
            bool vertical = props[2] != 1;
            vec2 pos((0.5f + x) * 24.0f, (0.5f + y) * 24.0f);
            unsigned int dir = 0;
            if (vertical) {
                pos.x += 12;
            }
            else {
                pos.y += 12;
                dir = 2;
            }
            if (props[3]) {
                vector<unsigned int> door(4);
                door[edat::EPROP_TYPE] = edat::ETYPE_DOOR_TRAP;
                door[edat::EPROP_X] = Helper_Editor_GetQuantizedPosition(pos.x) + offset;
                door[edat::EPROP_Y] = Helper_Editor_GetQuantizedPosition(pos.y);
                door[edat::EPROP_DIR] = dir;
                entities.push_back(door);
                vector<unsigned int> sw(3);
                sw[edat::EPROP_TYPE] = edat::ETYPE_SWITCH_TRAP;
                sw[edat::EPROP_X] = Helper_Editor_GetQuantizedPosition(props[0]) + offset;
                sw[edat::EPROP_Y] = Helper_Editor_GetQuantizedPosition(props[1]);
                entities.push_back(sw);
            }
            else if (props[6]) {
                vector<unsigned int> door(4);
                door[edat::EPROP_TYPE] = edat::ETYPE_DOOR_LOCKED;
                door[edat::EPROP_X] = Helper_Editor_GetQuantizedPosition(pos.x) + offset;
                door[edat::EPROP_Y] = Helper_Editor_GetQuantizedPosition(pos.y);
                door[edat::EPROP_DIR] = dir;
                entities.push_back(door);
                vector<unsigned int> sw(3);
                sw[edat::EPROP_TYPE] = edat::ETYPE_SWITCH_LOCKED;
                sw[edat::EPROP_X] = Helper_Editor_GetQuantizedPosition(props[0]) + offset;
                sw[edat::EPROP_Y] = Helper_Editor_GetQuantizedPosition(props[1]);
                entities.push_back(sw);
            }
            else {
                vector<unsigned int> door(4);
                door[edat::EPROP_TYPE] = edat::ETYPE_DOOR_REGULAR;
                door[edat::EPROP_X] = Helper_Editor_GetQuantizedPosition(pos.x) + offset;
                door[edat::EPROP_Y] = Helper_Editor_GetQuantizedPosition(pos.y);
                door[edat::EPROP_DIR] = dir;
                entities.push_back(door);
            }
        }
    }
    else if (type == OLDDATA_OBJTYPE_THWOMP) {
        if (props.size() == 3) {
            vector<unsigned int> e(4);
            e[edat::EPROP_TYPE] = edat::ETYPE_THWOMP;
            e[edat::EPROP_X] = Helper_Editor_GetQuantizedPosition(props[0]) + offset;
            e[edat::EPROP_Y] = Helper_Editor_GetQuantizedPosition(props[1]);
            e[edat::EPROP_DIR] = Helper_Editor_OldDirEnumToNewDirEnum(props[2]);
            entities.push_back(e);
        }
    }
    else if (type == OLDDATA_OBJTYPE_TURRET) {
        if (props.size() == 2) {
            vector<unsigned int> e(3);
            e[edat::EPROP_TYPE] = edat::ETYPE_TURRET;
            e[edat::EPROP_X] = Helper_Editor_GetQuantizedPosition(props[0]) + offset;
            e[edat::EPROP_Y] = Helper_Editor_GetQuantizedPosition(props[1]);
            entities.push_back(e);
        }
    }
    else if (type == OLDDATA_OBJTYPE_PLAYER) {
        if (props.size() == 2) {
            vector<unsigned int> e(3);
            e[edat::EPROP_TYPE] = edat::ETYPE_PLAYER;
            e[edat::EPROP_X] = Helper_Editor_GetQuantizedPosition(props[0]) + offset;
            e[edat::EPROP_Y] = Helper_Editor_GetQuantizedPosition(props[1]);
            entities.push_back(e);
        }
    }
}

unsigned int sim_loader::Helper_Editor_GetQuantizedPosition(double value) {
    return value / edat::quantize_step_size;
}

unsigned int sim_loader::Helper_Editor_OldDirEnumToNewDirEnum(int oldDirEnum) {
    return oldDirEnum * 2;
}

int sim_loader::Helper_Editor_NewDirEnumToOldDirEnum(unsigned int newDirEnum) {
    return newDirEnum / 2;
}

unsigned int sim_loader::Helper_Editor_VecToDirEnum(double x, double y) {
    if (x == 0) {
        if (y == 0) {
            return 0;
        }
        if (y < 1) {
            return edat::DIR_U;
        }
        return edat::DIR_D;
    }
    if (y == 0) {
        if (x == 0) {
            return 0;
        }
        if (x < 1) {
            return edat::DIR_L;
        }
        return edat::DIR_R;
    }
    if (x < 0) {
        if (y < 0) {
            return edat::DIR_LU;
        }
        return edat::DIR_LD;
    }
    if (y < 0) {
        return edat::DIR_RU;
    }
    return edat::DIR_RD;
}

Simulator* sim_loader::LoadFromSave(appSave& appState, const vector<int>& playerKeys, const vector<unsigned int>& playerColors, SimpleInput& input) {
    mathutils::GenerateNewRandomSeed();

    vector<int> tileIDGrid = appState.tiles;
    Grid_Segment* gridSegment = appState.segGrid->Clone();
    Grid_Edges* gridEdges = appState.edgeGrid->Clone();
    Grid_Entity* gridEntity = new Grid_Entity(Simulator::GRID_NUM_COLS, Simulator::GRID_NUM_ROWS, Simulator::GRID_CELL_SIZE);

    vector<Entity_Base*> entities;

    LoadFromSave_Entities(appState.entityState, gridSegment, gridEdges, gridEntity, entities);

    vector<Ninja*> ninjas(appState.ninjaState.size());

    for (size_t i = 0; i < appState.ninjaState.size(); ++i) {
        InputSource_Base* inputSource = nullptr;
        
        ByteArray* frames = new ByteArray();
        frames->writeBytes(appState.ninjaState[i].frames);
        frames->setPosition(appState.frameNum);
        
        if (!appState.isReplay) {
            inputSource = new InputSource_Recorder(input, frames, playerKeys[i * 3 % playerKeys.size()], playerKeys[(i * 3 + 1) % playerKeys.size()], playerKeys[(i * 3 + 2) % playerKeys.size()]);
        } else {
            inputSource = new InputSource_Playback(frames);
        }
        
        ninjas[i] = new Ninja(appState.ninjaState[i], inputSource);
    }

    return new Simulator(appState, tileIDGrid, gridSegment, gridEdges, gridEntity, entities, ninjas);
}

void sim_loader::LoadFromSave_Entities(vector<entitySave>& entityState, Grid_Segment* gridSegment, Grid_Edges* gridEdges, Grid_Entity* gridEntity, vector<Entity_Base*>& entities) {
    Entity_ExitDoor* lastExitDoor = nullptr;
    for (entitySave& entity : entityState) {
        switch(entity.etype) {
            case edat::ETYPE_MINE: {
                Entity_Mine* mine = new Entity_Mine(gridEntity, entity);
                Helper_RegisterEntity(entities, mine);
                }break;
            case edat::ETYPE_GOLD: {
                Entity_Gold* gold = new Entity_Gold(gridEntity, entity);
                Helper_RegisterEntity(entities, gold);
                }break;
            case edat::ETYPE_DOOR_REGULAR: {
                Entity_Door_Regular* regularDoor = new Entity_Door_Regular(gridEntity, entity, gridSegment, gridEdges);
                Helper_RegisterEntity(entities, regularDoor);
                }break;
            case edat::ETYPE_DOOR_LOCKED: {
                Entity_Door_Locked* lockedDoor = new Entity_Door_Locked(gridEntity, entity, gridSegment, gridEdges);
                Helper_RegisterEntity(entities, lockedDoor);
                }break;
            case edat::ETYPE_SWITCH_LOCKED: {
                // ERROR
                }break;
            case edat::ETYPE_DOOR_TRAP: {
                Entity_Door_Trap* trapDoor = new Entity_Door_Trap(gridEntity, entity, gridSegment, gridEdges);
                Helper_RegisterEntity(entities, trapDoor);
                }break;
            case edat::ETYPE_SWITCH_TRAP: {
                // ERROR
                }break;
            case edat::ETYPE_ONEWAY: {
                Entity_OnewayPlatform* onewayPlatform = new Entity_OnewayPlatform(gridEntity, entity);
                Helper_RegisterEntity(entities, onewayPlatform);
                }break;
            case edat::ETYPE_EXIT_DOOR: {
                Entity_ExitDoor* exitDoor = new Entity_ExitDoor(gridEntity, entity);
                lastExitDoor = exitDoor;
                Helper_RegisterEntity(entities, exitDoor);
                }break;
            case edat::ETYPE_EXIT_SWITCH: {
                Entity_ExitSwitch* exitSwitch = new Entity_ExitSwitch(gridEntity, entity, lastExitDoor);
                Helper_RegisterEntity(entities, exitSwitch);
                }break;
            case edat::ETYPE_CHAINGUN: {
                Entity_Drone_Chaingun* chaingunDrone = new Entity_Drone_Chaingun(gridEntity, entity);
                Helper_RegisterEntity(entities, chaingunDrone);
                }break;
            case edat::ETYPE_LASER: {
                Entity_Drone_Laser* laserDrone = new Entity_Drone_Laser(gridEntity, entity);
                Helper_RegisterEntity(entities, laserDrone);
                }break;
            case edat::ETYPE_ZAP: {
                Entity_Drone_Zap* zapDrone = new Entity_Drone_Zap(gridEntity, entity);
                Helper_RegisterEntity(entities, zapDrone);
                }break;
            case edat::ETYPE_CHASER: {
                Entity_Drone_Chaser* chaserDrone = new Entity_Drone_Chaser(gridEntity, entity);
                Helper_RegisterEntity(entities, chaserDrone);
                }break;
            case edat::ETYPE_FLOORGUARD: {
                Entity_FloorGuard* floorGuard = new Entity_FloorGuard(gridEntity, entity);
                Helper_RegisterEntity(entities, floorGuard);
                }break;
            case edat::ETYPE_LAUNCHPAD: {
                Entity_Launchpad* launchpad = new Entity_Launchpad(gridEntity, entity);
                Helper_RegisterEntity(entities, launchpad);
                }break;
            case edat::ETYPE_BOUNCEBLOCK: {
                Entity_BounceBlock* bounceBlock = new Entity_BounceBlock(gridEntity, entity);
                Helper_RegisterEntity(entities, bounceBlock);
                }break;
            case edat::ETYPE_ROCKET: {
                Entity_Rocket* rocket = new Entity_Rocket(gridEntity, entity);
                Helper_RegisterEntity(entities, rocket);
                }break;
            case edat::ETYPE_TURRET: {
                Entity_Turret* turret = new Entity_Turret(gridEntity, entity);
                Helper_RegisterEntity(entities, turret);
                }break;
            case edat::ETYPE_THWOMP: {
                Entity_Thwomp* thwomp = new Entity_Thwomp(gridEntity, entity);
                Helper_RegisterEntity(entities, thwomp);
                }break;
            default:
                // ERROR
                break;
        }
    }
}