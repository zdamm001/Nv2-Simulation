#pragma once

#include "..\\..\\math\\vec2.h"
#include "EntityGraphics.h"

class Entity_Drone_Chaser;

class EntityGraphics_Drone_Chaser : public EntityGraphics {
    public:
        static const int ANIM_IDLE = 0;
        static const int ANIM_CHASE = 1;
    private:
        MovieClip* mc_body;
        MovieClip* mc_eye;
        Entity_Drone_Chaser* entity;
    public:
        vec2 pos;
        double orn;
        int anim;
        EntityGraphics_Drone_Chaser(Entity_Drone_Chaser* entity);
        virtual ~EntityGraphics_Drone_Chaser();
        virtual void RegisterGraphics(vector<DisplayObject*>& displayObjects) override;
        virtual void UpdateState() override;
};