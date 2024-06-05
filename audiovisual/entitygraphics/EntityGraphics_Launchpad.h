#pragma once

#include "EntityGraphics.h"

class Entity_Launchpad;

class EntityGraphics_Launchpad : public EntityGraphics {
    public:
        static const int ANIM_IDLE = 0;
        static const int ANIM_LAUNCH = 1;
    private:
        MovieClip* mc;
        Entity_Launchpad* entity;
    public:
        int anim;
        EntityGraphics_Launchpad(Entity_Launchpad* entity, double x, double y, double rotation);
        virtual ~EntityGraphics_Launchpad();
        virtual void RegisterGraphics(vector<DisplayObject*>& displayObjects) override;
        virtual void UpdateState() override;
};