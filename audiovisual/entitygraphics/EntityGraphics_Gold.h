#pragma once

#include "EntityGraphics.h"

class Entity_Gold;

class EntityGraphics_Gold : public EntityGraphics {
    public:
        static const int ANIM_NOT_COLLECTED = 0;
        static const int ANIM_COLLECTED = 1;
    private:
        MovieClip* mc;
        Entity_Gold* entity;
    public:
        int anim;
        EntityGraphics_Gold(Entity_Gold* entity, double posx, double posy);
        virtual ~EntityGraphics_Gold();
        virtual void RegisterGraphics(vector<DisplayObject*>& graphics);
        virtual void UpdateState() override;
};