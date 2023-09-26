#pragma once
#include "InputSource_Base.h"

class InputSource_Playback : public InputSource_Base {
    private:
        bool is_finished;
    public:
        InputSource_Playback(ByteArray* frames);
        bool IsReplayFinished() override;
        void Tick(unsigned int frameNum) override;
};
