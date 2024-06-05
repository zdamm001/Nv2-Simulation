#pragma once

#include "EntityGraphics.h"

class Entity_Door_Locked;

class EntityGraphics_Door_Locked : public EntityGraphics {
    public:
        static const int ANIM_CLOSE = 0;
        static const int ANIM_OPEN = 1;
    private:
        MovieClip* mc_door;
        MovieClip* mc_switch;
        Entity_Door_Locked* entity;
    public:
        int anim;
        EntityGraphics_Door_Locked(Entity_Door_Locked* entity, double doorX, double doorY, double rotation, double switchX, double switchY);
        virtual ~EntityGraphics_Door_Locked();
        virtual void RegisterGraphics(vector<DisplayObject*>& displayObjects) override;
        virtual void UpdateState() override;
};