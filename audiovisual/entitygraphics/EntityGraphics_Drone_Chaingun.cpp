#include "EntityGraphics_Drone_Chaingun.h"
#include "..\\..\\simulation\\entities\\Entity_Drone_Chaingun.h"

EntityGraphics_Drone_Chaingun::EntityGraphics_Drone_Chaingun(Entity_Drone_Chaingun* entity)
    : entity(entity), pos(0, 0), orn(0), anim(ANIM_MOVE) {
    mc_body = new MovieClip(); //new asset_gfx_drone_chaingun();
    mc_eye = new MovieClip(); //new asset_gfx_drone_chaingun_eye();
    //mc_body->addChild(mc_eye);
    //mc_body->gotoAndStop("move");
}

EntityGraphics_Drone_Chaingun::~EntityGraphics_Drone_Chaingun() {
    delete mc_body;
    delete mc_eye;
}

void EntityGraphics_Drone_Chaingun::RegisterGraphics(vector<DisplayObject*>& displayObjects) {
    displayObjects.push_back(mc_body);
}

void EntityGraphics_Drone_Chaingun::UpdateState() {
    int prevAnim = anim;
    entity->GFX_UpdateState(this);
    mc_body->x = pos.x;
    mc_body->y = pos.y;
    mc_eye->rotation = orn / M_PI * 180;
    if (anim != prevAnim) {
        if (anim == ANIM_MOVE) {
            // mc_body->gotoAndStop("move");
        } else if (anim == ANIM_PREFIRE) {
            // mc_body->gotoAndPlay("prefire");
        } else if (anim == ANIM_POSTFIRE) {
            // mc_body->gotoAndPlay("postfire");
        } else if (anim == ANIM_FIRING) {
            // mc_body->gotoAndStop("fire");
        }
    }
}