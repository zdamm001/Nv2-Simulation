#include "SimpleInput.h"

SimpleInput::SimpleInput(/*IEventDispatcher dispatcher*/) {
    //localroot = dispatcher;
    //localroot.addEventListener(MouseEvent.MOUSE_MOVE, PRIVATE_EVENT_MouseMoved());
    //localroot.addEventListener(MouseEvent.MOUSE_DOWN, PRIVATE_EVENT_MouseDown());
    //localroot.addEventListener(MouseEvent.MOUSE_UP, PRIVATE_EVENT_MouseUp());
    //localroot.addEventListener(KeyboardEvent.KEY_DOWN, PRIVATE_EVENT_KeyDown());
    //localroot.addEventListener(KeyboardEvent.KEY_UP, PRIVATE_EVENT_KeyUp());
    Init();
}

void SimpleInput::Init() {
    mouseIsDown = false;
    mouseWasDown = false;
    posx = 0;
    posy = 0;
    oldx = 0;
    oldy = 0;
    downposx = 0;
    downposy = 0;
    upposx = 0;
    upposy = 0;
    stateDown = false;
    statePressed = false;
    stateReleased = false;
    keys.resize(256, false);
    oldkeys.resize(256, false);
    keytriggers.resize(256, 0);
    Tick();
    Tick();
}

void SimpleInput::Tick() {
    for (int i = 0; i < keytriggers.size(); i++) {
        keytriggers[i] = 0;
    }

    oldx = posx;
    oldy = posy;
    stateDown = false;
    statePressed = false;
    stateReleased = false;

    if (mouseIsDown) {
        stateDown = true;
        if (!mouseWasDown) {
            statePressed = true;
            downposx = xmouse;
            downposy = ymouse;
        }
    } else if (mouseWasDown) {
        stateReleased = true;
        upposx = xmouse;
        upposy = ymouse;
    }

    mouseWasDown = mouseIsDown;
    posx = xmouse;
    posy = ymouse;

    for (int i = 0; i < keys.size(); i++) {
        if (IsKeyDown(i)) {
            if (!oldkeys[i]) {
                keytriggers[i] = 1;
            }
        } else if (oldkeys[i]) {
            keytriggers[i] = -1;
        }
    }

    for (int i = 0; i < oldkeys.size(); i++) {
        oldkeys[i] = keys[i];
    }
}

vec2 SimpleInput::GetMousePos() {
    return vec2(xmouse, ymouse);
}

vec2 SimpleInput::GetMousePos_Down() {
    return vec2(downposx, downposy);
}

vec2 SimpleInput::GetMousePos_Up() {
    return vec2(upposx, upposy);
}

vec2 SimpleInput::GetMouseVel() {
    return vec2(posx - oldx, posy - oldy);
}

//void SimpleInput::PRIVATE_EVENT_MouseMoved(MouseEvent event) {
//    xmouse = event.stageX;
//    ymouse = event.stageY;
//}

//void SimpleInput::PRIVATE_EVENT_MouseDown(MouseEvent event) {
//    mouseIsDown = true;
//}

//void SimpleInput::PRIVATE_EVENT_MouseUp(MouseEvent event) {
//    mouseIsDown = false;
//}

bool SimpleInput::IsMouseDown() {
    return stateDown;
}

bool SimpleInput::IsMousePressed() {
    return statePressed;
}

bool SimpleInput::IsMouseReleased() {
    return stateReleased;
}

//void SimpleInput::PRIVATE_EVENT_KeyDown(KeyboardEvent event) {
//    keys[event.keyCode] = true;
//    keys[Keyboard.CONTROL] = event.ctrlKey;
//}

//void SimpleInput::PRIVATE_EVENT_KeyUp(KeyboardEvent event) {
//    keys[event.keyCode] = false;
//}

void SimpleInput::NEW_PRIVATE_EVENT_KeyDown(unsigned int key) {
    keys[key] = true;
}

void SimpleInput::NEW_PRIVATE_EVENT_KeyUp(unsigned int key) {
    keys[key] = false;
}

bool SimpleInput::IsKeyDown(unsigned int key) {
    return keys[key];
}

bool SimpleInput::IsOnePressed(vector<int>& keyList) {
    for (int i = 0; i < keyList.size(); ++i) {
        if (keytriggers[keyList[i]] > 0) {
            return true;
        }
    }
    return false;
}

bool SimpleInput::IsKeyPressed(unsigned int key) {
    return keytriggers[key] > 0;
}

bool SimpleInput::IsKeyReleased(unsigned int key) {
    return keytriggers[key] < 0;
}

bool SimpleInput::IsAnyKeyPressed() {
    //return keytriggers.indexOf(1) != -1;
    return find(keytriggers.begin(), keytriggers.end(), 1) != keytriggers.end();
}

bool SimpleInput::CapsLock() {
    //return Keyboard::capsLock;
}