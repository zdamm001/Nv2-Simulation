#pragma once

#include "EntityGraphics.h"
#include "..\\..\\math\\vec2.h"

class Entity_BounceBlock;

class EntityGraphics_BounceBlock : public EntityGraphics {
    private:
        MovieClip* mc;
        Entity_BounceBlock* entity;
    public:
        vec2 pos;
        EntityGraphics_BounceBlock(Entity_BounceBlock* entity);
        virtual ~EntityGraphics_BounceBlock();
        virtual void RegisterGraphics(vector<DisplayObject*>& graphics);
        virtual void UpdateState() override;
};