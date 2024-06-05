#include "EntityGraphics_OnewayPlatform.h"
#include "../../simulation/entities/Entity_OnewayPlatform.h"

EntityGraphics_OnewayPlatform::EntityGraphics_OnewayPlatform(double x, double y, double rotation) {
    mc = new MovieClip(); // new asset_gfx_oneway();
    mc->x = x;
    mc->y = y;
    mc->rotation = rotation / M_PI * 180;
    mc->cacheAsBitmap = true;
}

EntityGraphics_OnewayPlatform::~EntityGraphics_OnewayPlatform() {
    delete mc;
}

void EntityGraphics_OnewayPlatform::RegisterGraphics(vector<DisplayObject*>& displayObjects) {
    displayObjects.insert(displayObjects.begin(), mc);
}

void EntityGraphics_OnewayPlatform::UpdateState() {
    
}