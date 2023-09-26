#pragma once

#include "InputSource_Base.h"
//#include "..\\simpleFramework\\SimpleInput.h"
class SimpleInput;

class InputSource_Recorder : public InputSource_Base {
    private:
        SimpleInput& input;
        unsigned int keycode_J;
        unsigned int keycode_L;
        unsigned int keycode_R;
    public:
        InputSource_Recorder(SimpleInput& input, unsigned int keyJ, unsigned int keyL, unsigned int keyR);
        void Tick(unsigned int frameNum) override;
};
