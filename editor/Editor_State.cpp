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
        return Editor_State();
    }

    for (int i = 0; i < editorState.tileIDs.size(); ++i) {
        editorState.tileIDs[i] = bytes.readUnsignedByte();
    }

    for (int i = 0; i < edat::num_structtypes; ++i) {
        if (bytes.bytesAvailable() < 2) {
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
                    return Editor_State();
                }
                for (int k = 0; k < edat::STRUCT_SIZE[i]; ++k) {
                    entityData.push_back(bytes.readUnsignedByte());
                }
                editorState.entities.push_back(entityData);
            }
        }

        size_t entityDataSize = bytes.getPosition() - startPos;
        size_t expectedSize = numEntities * edat::STRUCT_SIZE[i];
        if (entityDataSize != expectedSize) {
            // WARNING! Editor_State.Load_From_Bytes() read the wrong number of bytes
        }
    }

    return editorState;
}