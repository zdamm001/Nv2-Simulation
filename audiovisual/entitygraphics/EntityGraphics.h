#pragma once
#include <vector>

//#include "..\\..\\flash\\display\\DisplayObject.h"
class DisplayObject {public: bool cacheAsBitmap; double rotation; double scaleX; double scaleY; double visible; double x; double y;};
class DisplayObjectContainer : public DisplayObject {}; //addChild
class Sprite : public DisplayObjectContainer {}; //graphics
class MovieClip : public Sprite {public: int currentFrame;}; //gotoAndPlay/Stop

using namespace std;

class EntityGraphics {
    public:
        virtual ~EntityGraphics() = default;
        virtual void RegisterGraphics(vector<DisplayObject*>&) = 0;
        virtual void UpdateState() = 0;
};