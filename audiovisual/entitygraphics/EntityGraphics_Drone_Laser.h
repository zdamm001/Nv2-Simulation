#pragma once

#include "..\\..\\math\\vec2.h"
#include "EntityGraphics.h"

class Entity_Drone_Laser;
class Sprite;

class EntityGraphics_Drone_Laser : public EntityGraphics {
    public:
        static const int ANIM_MOVE = 0;
        static const int ANIM_PREFIRE = 1;
        static const int ANIM_FIRING = 2;
        static const int ANIM_POSTFIRE = 3;
    private:
        MovieClip* mc_body;
        MovieClip* mc_eye;
        MovieClip* mc_blast;
        Sprite* mc_beam;
        Entity_Drone_Laser* entity;
    public:
        vec2 pos;
        double orn;
        int anim;
        vec2 blast_pos;
        double blast_scale;
        EntityGraphics_Drone_Laser(Entity_Drone_Laser* entity);
        virtual ~EntityGraphics_Drone_Laser();
        virtual void RegisterGraphics(vector<DisplayObject*>& displayObjects) override;
        virtual void UpdateState() override;
};