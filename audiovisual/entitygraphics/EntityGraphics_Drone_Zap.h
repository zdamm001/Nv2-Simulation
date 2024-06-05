#pragma once

#include "..\\..\\math\\vec2.h"
#include "EntityGraphics.h"

class Entity_Drone_Zap;

class EntityGraphics_Drone_Zap : public EntityGraphics {
    private:
        MovieClip* mc_body;
        MovieClip* mc_eye;
        Entity_Drone_Zap* entity;
    public:
        vec2 pos;
        double orn;
        EntityGraphics_Drone_Zap(Entity_Drone_Zap* entity);
        virtual ~EntityGraphics_Drone_Zap();
        virtual void RegisterGraphics(vector<DisplayObject*>& displayObjects) override;
        virtual void UpdateState() override;
};