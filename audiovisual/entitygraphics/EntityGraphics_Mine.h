#pragma once

#include "EntityGraphics.h"

class Entity_Mine;

class EntityGraphics_Mine : public EntityGraphics {
    public:
        static const int ANIM_UNEXPLODED = 0;
        static const int ANIM_EXPLODED = 1;
    private:
        MovieClip* mc;
        Entity_Mine* entity;
    public:
        int anim;
        EntityGraphics_Mine(Entity_Mine* entity, double x, double y);
        virtual ~EntityGraphics_Mine();
        virtual void RegisterGraphics(vector<DisplayObject*>& graphics);
        virtual void UpdateState() override;
};