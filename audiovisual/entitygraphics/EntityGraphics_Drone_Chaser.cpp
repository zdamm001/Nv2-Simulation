#include "EntityGraphics_Drone_Chaser.h"
#include "..\\..\\simulation\\entities\\Entity_Drone_Chaser.h"

EntityGraphics_Drone_Chaser::EntityGraphics_Drone_Chaser(Entity_Drone_Chaser* entity)
    : entity(entity), pos(0, 0), orn(0), anim(ANIM_IDLE) {
    mc_body = new MovieClip(); // new asset_gfx_drone_chaser();
    mc_eye = new MovieClip(); // new asset_gfx_drone_eye();
    mc_body->cacheAsBitmap = true;
    //mc_body->gotoAndStop("idle");
}

EntityGraphics_Drone_Chaser::~EntityGraphics_Drone_Chaser() {
    delete mc_body;
    delete mc_eye;
}

void EntityGraphics_Drone_Chaser::RegisterGraphics(vector<DisplayObject*>& displayObjects) {
    displayObjects.push_back(mc_body);
    displayObjects.push_back(mc_eye);
}

void EntityGraphics_Drone_Chaser::UpdateState() {
    int prevAnim = anim;
    entity->GFX_UpdateState(this);
    mc_body->x = pos.x;
    mc_body->y = pos.y;
    mc_eye->x = pos.x;
    mc_eye->y = pos.y;
    mc_eye->rotation = orn / M_PI * 180;
    if (anim == ANIM_CHASE) {
        // mc_body->gotoAndPlay("chase");
        anim = ANIM_IDLE;
    } else if (anim == ANIM_IDLE) {
        // mc_body->gotoAndStop("idle");
    }
}