#pragma once

#include "EntityGraphics.h"
#include "..\\..\\math\\vec2.h"

class Entity_FloorGuard;

class EntityGraphics_FloorGuard : public EntityGraphics {
    public:
        static const int ANIM_IDLE = 0;
        static const int ANIM_CHASE_L = -1;
        static const int ANIM_CHASE_R = 1;
    private:
        MovieClip* mc;
        Entity_FloorGuard* entity;
    public:
        vec2 pos;
        int anim;
        EntityGraphics_FloorGuard(Entity_FloorGuard* entity);
        virtual ~EntityGraphics_FloorGuard();
        virtual void RegisterGraphics(vector<DisplayObject*>& graphics);
        virtual void UpdateState() override;
};