#pragma once

#include "..\\..\\math\\vec2.h"
#include "EntityGraphics.h"

class Entity_Turret;

class EntityGraphics_Turret : public EntityGraphics {
    public:
        static const int ANIM_IDLE = 0;
        static const int ANIM_PREFIRE = 1;
        static const int ANIM_FIRING = 2;
        static const int ANIM_POSTFIRE = 3;
        static const int CROSSHAIR_OFF = 0;
        static const int CROSSHAIR_FAR = 1;
        static const int CROSSHAIR_MID = 2;
        static const int CROSSHAIR_NEAR = 3;
        static const int CROSSHAIR_PREFIRE = 4;
        static const int CROSSHAIR_POSTFIRE = 5;
    private:
        MovieClip* mc_base;
        MovieClip* mc_crosshair;
        Entity_Turret* entity;
    public:
        int anim_base;
        vec2 pos_crosshair;
        int anim_crosshair;
    public:
        EntityGraphics_Turret(Entity_Turret* entity, double x, double y);
        virtual ~EntityGraphics_Turret();
        virtual void RegisterGraphics(vector<DisplayObject*>& displayObjects) override;
        virtual void UpdateState() override;
};