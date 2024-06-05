#include "EntityGraphics_Thwomp.h"
#include "../../simulation/entities/Entity_Thwomp.h"

EntityGraphics_Thwomp::EntityGraphics_Thwomp(Entity_Thwomp* entity, double rotation)
    : entity(entity), pos(0, 0) {
    mc = new MovieClip(); // new asset_gfx_thwomp();
    // mc->gotoAndStop("idle");
    mc->rotation = rotation / M_PI * 180;
    mc->cacheAsBitmap = true;
}

EntityGraphics_Thwomp::~EntityGraphics_Thwomp() {
    delete mc;
}

void EntityGraphics_Thwomp::RegisterGraphics(vector<DisplayObject*>& displayObjects) {
    displayObjects.push_back(mc);
}

void EntityGraphics_Thwomp::UpdateState() {
    entity->GFX_UpdateState(this);
    mc->x = pos.x;
    mc->y = pos.y;
}