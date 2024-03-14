#include "InputSource_Playback.h"

InputSource_Playback::InputSource_Playback(ByteArray* frames) : InputSource_Base(frames), is_finished(false) {}

bool InputSource_Playback::IsReplayFinished() {
    return is_finished;
}

void InputSource_Playback::Tick(unsigned int frameNum) {
    if (frameNum >= frames->length()) {
        current_J = false;
        current_L = false;
        current_R = false;
        is_finished = true;
    }
    else {
        frames->setPosition(frameNum);
        int inputByte = frames->readByte();
        current_J = (inputByte & bit_J) > 0;
        current_L = (inputByte & bit_L) > 0;
        current_R = (inputByte & bit_R) > 0;
    }
}

void InputSource_Playback::saveState(ByteArray& state) {
    unsigned int length = frames->length();
    state.writeBytes(*frames, 0, length);
}