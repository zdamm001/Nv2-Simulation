#include "InputSource_Recorder.h"

InputSource_Recorder::InputSource_Recorder(SimpleInput& input, unsigned int keyJ, unsigned int keyL, unsigned int keyR)
    : input(input), keycode_J(keyJ), keycode_L(keyL), keycode_R(keyR), InputSource_Base(new ByteArray()) {
    frames->length(4096);
}

void InputSource_Recorder::Tick(unsigned int frameNum) {
    //current_J = input.IsKeyDown(keycode_J);
    //current_L = input.IsKeyDown(keycode_L);
    //current_R = input.IsKeyDown(keycode_R);

    if (frameNum >= frames->length()) {
        frames->length(frameNum * 2);
    }

    unsigned char keys = 0;
    if (current_J) {
        keys |= bit_J;
    }
    if (current_L) {
        keys |= bit_L;
    }
    if (current_R) {
        keys |= bit_R;
    }

    frames->setPosition(frameNum);
    frames->writeByte(keys);
}