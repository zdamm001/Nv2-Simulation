#pragma once

#include "EntityGraphics.h"

class Entity_Door_Regular;

class EntityGraphics_Door_Regular : public EntityGraphics {
    public:
        static const int ANIM_CLOSE = 0;
        static const int ANIM_OPEN = 1;
    private:
        MovieClip* mc_door;
        Entity_Door_Regular* entity;
    public:
        int anim;
        EntityGraphics_Door_Regular(Entity_Door_Regular* entity, double x, double y, double rotation);
        virtual ~EntityGraphics_Door_Regular();
        virtual void RegisterGraphics(vector<DisplayObject*>& displayObjects) override;
        virtual void UpdateState() override;
};