#pragma once
#include <vector>
#include <algorithm>

// #include "..\\flash\\events\\IEventDispatcher.h"
// #include "..\\flash\\events\\KeyboardEvent.h"
// #include "..\\flash\\events\\MouseEvent.h"
// #include "..\\flash\\ui\\Keyboard.h"
#include "..\\math\\vec2.h"

using namespace std;

class SimpleInput {
    private:
        //IEventDispatcher localroot;
        double xmouse;
        double ymouse;
        bool mouseWasDown;
        bool mouseIsDown;
        bool stateDown;
        bool statePressed;
        bool stateReleased;
        double posx;
        double posy;
        double oldx;
        double oldy;
        double downposx;
        double downposy;
        double upposx;
        double upposy;
        vector<bool> keys;
        vector<bool> oldkeys;
        vector<int> keytriggers;
    public:
        SimpleInput();
    private:
        void Init();
    public:
        void Tick();
        vec2 GetMousePos();
        vec2 GetMousePos_Down();
        vec2 GetMousePos_Up();
        vec2 GetMouseVel();
        //void PRIVATE_EVENT_MouseMoved(MouseEvent event);
        //void PRIVATE_EVENT_MouseDown(MouseEvent event);
        //void PRIVATE_EVENT_MouseUp(MouseEvent event);
        bool IsMouseDown();
        bool IsMousePressed();
        bool IsMouseReleased();
        //void PRIVATE_EVENT_KeyDown(KeyboardEvent event);
        //void PRIVATE_EVENT_KeyUp(KeyboardEvent event);
        void NEW_PRIVATE_EVENT_KeyDown(unsigned int key);
        void NEW_PRIVATE_EVENT_KeyUp(unsigned int key);
        bool IsKeyDown(unsigned int key);
        bool IsOnePressed(vector<int>& keyList);
        bool IsKeyPressed(unsigned int key);
        bool IsKeyReleased(unsigned int key);
        bool IsAnyKeyPressed();
        bool CapsLock();
};