#pragma once

#include "EntityGraphics.h"

class Entity_ExitSwitch;

class EntityGraphics_ExitSwitch : public EntityGraphics {
    public:
        static const int ANIM_CLOSED = 0;
        static const int ANIM_OPEN = 1;
    private:
        MovieClip* mc;
        Entity_ExitSwitch* entity;
    public:
        int anim;
        EntityGraphics_ExitSwitch(Entity_ExitSwitch* entity, double x, double y);
        virtual ~EntityGraphics_ExitSwitch();
        virtual void RegisterGraphics(vector<DisplayObject*>& displayObjects) override;
        virtual void UpdateState() override;
};