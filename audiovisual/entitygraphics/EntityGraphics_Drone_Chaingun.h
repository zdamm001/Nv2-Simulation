#pragma once

#include "..\\..\\math\\vec2.h"
#include "EntityGraphics.h"

class Entity_Drone_Chaingun;

class EntityGraphics_Drone_Chaingun : public EntityGraphics {
    public:
        static const int ANIM_MOVE = 0;
        static const int ANIM_PREFIRE = 1;
        static const int ANIM_FIRING = 2;
        static const int ANIM_POSTFIRE = 3;
    private:
        MovieClip* mc_body;
        MovieClip* mc_eye;
        Entity_Drone_Chaingun* entity;
    public:
        vec2 pos;
        double orn;
        int anim;
        EntityGraphics_Drone_Chaingun(Entity_Drone_Chaingun* entity);
        virtual ~EntityGraphics_Drone_Chaingun();
        virtual void RegisterGraphics(vector<DisplayObject*>& displayObjects) override;
        virtual void UpdateState() override;
};