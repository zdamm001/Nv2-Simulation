#pragma once

#include "..\\..\\math\\vec2.h"
#include "EntityGraphics.h"

class Entity_Rocket;

class EntityGraphics_Rocket : public EntityGraphics {
    public:
        static const int ANIM_IDLE = 0;
        static const int ANIM_FIRE = 1;
        static const int ANIM_EXPLODE = 2;
    private:
        MovieClip* mc_base;
        MovieClip* mc_rocket;
        Entity_Rocket* entity;
    public:
        int anim_base;
        vec2 pos_rocket;
        double orn_rocket;
        bool is_rocket_active;
    public:
        EntityGraphics_Rocket(Entity_Rocket* entity, double x, double y);
        virtual ~EntityGraphics_Rocket();
        virtual void RegisterGraphics(vector<DisplayObject*>& displayObjects) override;
        virtual void UpdateState() override;
};