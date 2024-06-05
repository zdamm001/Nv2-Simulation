#pragma once

#include "..\\..\\math\\vec2.h"
#include "EntityGraphics.h"

class Entity_Door_Trap;

class EntityGraphics_Door_Trap : public EntityGraphics {
    public:
        static const int ANIM_CLOSE = 0;
        static const int ANIM_OPEN = 1;
    private:
        MovieClip* mc_door;
        MovieClip* mc_switch;
        Entity_Door_Trap* entity;
    public:
        int anim;
        EntityGraphics_Door_Trap(Entity_Door_Trap* entity, double doorX, double doorY, double rotation, double switchX, double switchY);
        virtual ~EntityGraphics_Door_Trap();
        virtual void RegisterGraphics(vector<DisplayObject*>& displayObjects) override;
        virtual void UpdateState() override;
};