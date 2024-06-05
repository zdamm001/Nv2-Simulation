#pragma once

#include "..\\..\\math\\vec2.h"
#include "EntityGraphics.h"

class Entity_Thwomp;

class EntityGraphics_Thwomp : public EntityGraphics {
    private:
        MovieClip* mc;
        Entity_Thwomp* entity;
    public:
        vec2 pos;
        EntityGraphics_Thwomp(Entity_Thwomp* entity, double rotation);
        virtual ~EntityGraphics_Thwomp();
        virtual void RegisterGraphics(vector<DisplayObject*>& displayObjects) override;
        virtual void UpdateState() override;
};