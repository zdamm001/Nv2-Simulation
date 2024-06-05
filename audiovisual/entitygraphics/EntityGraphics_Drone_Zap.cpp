#include "EntityGraphics_Drone_Zap.h"
#include "../../simulation/entities/Entity_Drone_Zap.h"

EntityGraphics_Drone_Zap::EntityGraphics_Drone_Zap(Entity_Drone_Zap* entity)
    : entity(entity), pos(0, 0), orn(0) {
    mc_body = new MovieClip(); // new asset_gfx_drone_zap();
    mc_eye = new MovieClip(); // new asset_gfx_drone_eye();
    mc_body->cacheAsBitmap = true;
}

EntityGraphics_Drone_Zap::~EntityGraphics_Drone_Zap() {
    delete mc_body;
    delete mc_eye;
}

void EntityGraphics_Drone_Zap::RegisterGraphics(vector<DisplayObject*>& displayObjects) {
    displayObjects.push_back(mc_body);
    displayObjects.push_back(mc_eye);
}

void EntityGraphics_Drone_Zap::UpdateState() {
    entity->GFX_UpdateState(this);
    mc_body->x = pos.x;
    mc_body->y = pos.y;
    mc_eye->x = pos.x;
    mc_eye->y = pos.y;
    mc_eye->rotation = orn / M_PI * 180;
}