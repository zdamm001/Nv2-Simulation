#pragma once

#include "EntityGraphics.h"

class Entity_OnewayPlatform;

class EntityGraphics_OnewayPlatform : public EntityGraphics {
    private:
        MovieClip* mc;
    public:
        EntityGraphics_OnewayPlatform(double x, double y, double rotation);
        virtual ~EntityGraphics_OnewayPlatform();
        virtual void RegisterGraphics(vector<DisplayObject*>& displayObjects) override;
        virtual void UpdateState() override;
};
