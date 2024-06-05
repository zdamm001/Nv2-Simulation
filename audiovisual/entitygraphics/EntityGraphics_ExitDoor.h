#pragma once

#include "EntityGraphics.h"

class Entity_ExitDoor;

class EntityGraphics_ExitDoor : public EntityGraphics {
    public:
        static const int ANIM_CLOSED = 0;
        static const int ANIM_OPEN = 1;
    private:
        MovieClip* mc;
        Entity_ExitDoor* entity;
    public:
        int anim;
        EntityGraphics_ExitDoor(Entity_ExitDoor* entity, double x, double y);
        virtual ~EntityGraphics_ExitDoor();
        virtual void RegisterGraphics(vector<DisplayObject*>& displayObjects) override;
        virtual void UpdateState() override;
};