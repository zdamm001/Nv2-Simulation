#pragma once
#include <string>

#include "..\\..\\flash\\utils\\ByteArray.h"
#include "..\\sim_globals.h"

class InputSource_Base {
    protected:
        static const int bit_J = 1;
        static const int bit_L = 2;
        static const int bit_R = 4;
        ByteArray* frames;
        bool current_J;
        bool current_L;
        bool current_R;
    public:
        InputSource_Base(ByteArray* frames);
        virtual ~InputSource_Base();
        ByteArray* DumpFrames();
        string DumpString();
        virtual bool IsReplayFinished();
        virtual void Tick(unsigned int frameNum);
        bool IsButtonDown_Jump();
        bool IsButtonDown_Left();
        bool IsButtonDown_Right();
        virtual void saveState(ByteArray& state);
};
