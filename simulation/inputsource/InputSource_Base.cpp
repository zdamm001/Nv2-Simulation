#include "InputSource_Base.h"

InputSource_Base::InputSource_Base(ByteArray* frames)
    : frames(frames), current_J(false), current_L(false), current_R(false) {}

InputSource_Base::~InputSource_Base() {
    delete frames;
}

ByteArray InputSource_Base::DumpFrames() {
    frames->setPosition(frames->length() - 1);

    while (frames->getPosition() >= 0) {
        if (frames->readByte() != 0) {
            break;
        }
        frames->setPosition(frames->getPosition() - 2);
    }

    unsigned int position = frames->getPosition();
    ByteArray result;
    result.setPosition(0);
    frames->setPosition(0);
    for (int i = 0; i <= position; ++i) {
        result.writeByte(frames->readByte());
    }

    return result;
}

string InputSource_Base::DumpString() {
    string result = sim_globals::BAtoString(*frames);
    int position = result.length() - 1;
    while (result[position] == '0' && position > 0) {
        position--;
    }
    return result.substr(0, position);
}

bool InputSource_Base::IsReplayFinished() {
    return false;
}

void InputSource_Base::Tick(unsigned int frameNum) {
    return;
}

bool InputSource_Base::IsButtonDown_Jump() {
    return current_J;
}

bool InputSource_Base::IsButtonDown_Left() {
    return current_L;
}

bool InputSource_Base::IsButtonDown_Right() {
    return current_R;
}

void InputSource_Base::saveState(ByteArray& state) {
    return;
}