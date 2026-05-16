#include "Editor_State.h"

Editor_State::Editor_State() : tileIDs(edat::num_cols * edat::num_rows) {}

Editor_State Editor_State::Load_From_Bytes(ByteArray& bytes) {
    Editor_State editorState;
    bytes.setPosition(0);
    bytes.readUnsignedByte();
    bytes.readUnsignedByte();
    bytes.readUnsignedByte();
    bytes.readUnsignedByte();

    if (bytes.bytesAvailable() < editorState.tileIDs.size()) {
        // "WARNING! Someone passed Load_From_Bytes() a bunch of bullshit; we didn\'t load it."
        return Editor_State();
    }

    for (size_t i = 0; i < editorState.tileIDs.size(); ++i) {
        editorState.tileIDs[i] = bytes.readUnsignedByte();
    }

    for (size_t i = 0; i < edat::num_structtypes; ++i) {
        if (bytes.bytesAvailable() < 2) {
            // "WARNING! Someone passed Load_From_Bytes() a bunch of bullshit; we didn\'t load it."
            return Editor_State();
        }
        short numEntities = bytes.readShort();
        unsigned int startPos = bytes.getPosition();
        for (int j = 0; j < numEntities; ++j) {
            vector<unsigned int> entityData, nextEntityData;
            entityData.push_back(edat::MAP_STRUCT_TO_ETYPE[i]);
            if (i == edat::STRUCTTYPE_EXIT) {
                nextEntityData.push_back(edat::ETYPE_EXIT_SWITCH);
                if (bytes.bytesAvailable() < 4) {
                    // "WARNING! Someone passed Load_From_Bytes() a bunch of bullshit; we didn\'t load it."
                    return Editor_State();
                }
                entityData.push_back(bytes.readUnsignedByte());
                entityData.push_back(bytes.readUnsignedByte());
                nextEntityData.push_back(bytes.readUnsignedByte());
                nextEntityData.push_back(bytes.readUnsignedByte());
                editorState.entities.push_back(entityData);
                editorState.entities.push_back(nextEntityData);
            }
            else if (i == edat::STRUCTTYPE_DOOR_LOCKED) {
                nextEntityData.push_back(edat::ETYPE_SWITCH_LOCKED);
                if (bytes.bytesAvailable() < 5) {
                    // "WARNING! Someone passed Load_From_Bytes() a bunch of bullshit; we didn\'t load it."
                    return Editor_State();
                }
                entityData.push_back(bytes.readUnsignedByte());
                entityData.push_back(bytes.readUnsignedByte());
                entityData.push_back(bytes.readUnsignedByte());
                nextEntityData.push_back(bytes.readUnsignedByte());
                nextEntityData.push_back(bytes.readUnsignedByte());
                editorState.entities.push_back(entityData);
                editorState.entities.push_back(nextEntityData);
            }
            else if (i == edat::STRUCTTYPE_DOOR_TRAP) {
                nextEntityData.push_back(edat::ETYPE_SWITCH_TRAP);
                if (bytes.bytesAvailable() < 5) {
                    // "WARNING! Someone passed Load_From_Bytes() a bunch of bullshit; we didn\'t load it."
                    return Editor_State();
                }
                entityData.push_back(bytes.readUnsignedByte());
                entityData.push_back(bytes.readUnsignedByte());
                entityData.push_back(bytes.readUnsignedByte());
                nextEntityData.push_back(bytes.readUnsignedByte());
                nextEntityData.push_back(bytes.readUnsignedByte());
                editorState.entities.push_back(entityData);
                editorState.entities.push_back(nextEntityData);
            }
            else {
                if (bytes.bytesAvailable() < edat::STRUCT_SIZE[i]) {
                    // "WARNING! Someone passed Load_From_Bytes() a bunch of bullshit; we didn\'t load it."
                    return Editor_State();
                }
                for (unsigned int k = 0; k < edat::STRUCT_SIZE[i]; ++k) {
                    entityData.push_back(bytes.readUnsignedByte());
                }
                editorState.entities.push_back(entityData);
            }
        }

        size_t entityDataSize = bytes.getPosition() - startPos;
        size_t expectedSize = numEntities * edat::STRUCT_SIZE[i];
        if (entityDataSize != expectedSize) {
            // "WARNING! Editor_State::Load_From_Bytes() read the wrong number of bytes" + entityDataSize + " , " + expectedSize
        }
    }

    return editorState;
}

ByteArray Editor_State::Save_To_Bytes(const Editor_State& state) {
    ByteArray bytes;
    bytes.setPosition(0);

    bytes.writeByte(0);
    bytes.writeByte(0);
    bytes.writeByte(0);
    bytes.writeByte(0);

    for (unsigned int tileID : state.tileIDs) {
        bytes.writeByte(tileID);
    }

    vector<vector<unsigned int>> propsByEtype(edat::num_etypes);

    for (size_t i = 0; i < state.entities.size(); ++i) {
        const vector<unsigned int>& entity = state.entities[i];
        unsigned int type = entity[0];

        for (size_t j = 1; j < entity.size(); ++j) {
            propsByEtype[type].push_back(entity[j]);
        }

        if (type == edat::ETYPE_EXIT_DOOR || type == edat::ETYPE_DOOR_LOCKED || type == edat::ETYPE_DOOR_TRAP) {
            if (i == state.entities.size() - 1) {
                // "WARNING! Editor_State::Save_To_Bytes() found a door at the end of the elist, with no switch!"
                break;
            }

            const vector<unsigned int>& nextEntity = state.entities[i + 1];

            for (size_t j = 1; j < nextEntity.size(); ++j) {
                propsByEtype[type].push_back(nextEntity[j]);
            }

            i++;
        }
    }

    vector<vector<unsigned int>> propsByStructType(edat::num_structtypes);

    for (size_t i = 0; i < edat::num_structtypes; ++i) {
        propsByStructType[i] = propsByEtype[edat::MAP_STRUCT_TO_ETYPE[i]];
    }

    for (size_t i = 0; i < edat::num_structtypes; ++i) {
        const vector<unsigned int>& props = propsByStructType[i];
        unsigned int structSize = edat::STRUCT_SIZE[i];

        if (props.size() % structSize != 0) {
            // "WARNING! Editor_State::Save_To_Bytes() has a property list with incorrect stride/size; type: " + i + ", bytes:" + props.size()
            bytes.writeShort(0);
            break;
        }

        unsigned int count = props.size() / structSize;
        bytes.writeShort(count);

        for (unsigned int value : props) {
            bytes.writeByte(value);
        }

        if (count * structSize != props.size()) {
            // "WARNING! Editor_State::Save_To_Bytes() is going crazy: " + count + "*" + structSize + " != " + props.size() + "?!"
            break;
        }
    }

    return bytes;
}