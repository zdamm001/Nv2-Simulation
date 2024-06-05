#include "EntityGraphics_Rocket.h"
#include "../../simulation/entities/Entity_Rocket.h"

EntityGraphics_Rocket::EntityGraphics_Rocket(Entity_Rocket* entity, double x, double y)
    : entity(entity), anim_base(ANIM_IDLE), pos_rocket(0, 0), orn_rocket(0), is_rocket_active(false) {
    mc_base = new MovieClip(); // new asset_gfx_rocket_base();
    mc_base->x = x;
    mc_base->y = y;
    // mc_base->gotoAndStop("idle");
    mc_base->cacheAsBitmap = true;
    mc_rocket = new MovieClip(); // new asset_gfx_rocket();
    mc_rocket->visible = false;
}

EntityGraphics_Rocket::~EntityGraphics_Rocket() {
    delete mc_base;
    delete mc_rocket;
}

void EntityGraphics_Rocket::RegisterGraphics(vector<DisplayObject*>& displayObjects) {
    displayObjects.insert(displayObjects.begin(), mc_base);
    displayObjects.push_back(mc_rocket);
}

void EntityGraphics_Rocket::UpdateState() {
    int prevAnim = anim_base;
    entity->GFX_UpdateState(this);
    if (anim_base != prevAnim) {
        if (anim_base == ANIM_IDLE) {
            // mc_base->gotoAndStop("idle");
        } else if (anim_base == ANIM_FIRE) {
            // mc_base->gotoAndPlay("fire");
        } else if (anim_base == ANIM_EXPLODE) {
            // mc_base->gotoAndPlay("explode");
        }
    }
    if (is_rocket_active) {
        mc_rocket->visible = true;
        mc_rocket->x = pos_rocket.x;
        mc_rocket->y = pos_rocket.y;
        mc_rocket->rotation = orn_rocket / M_PI * 180;
    } else {
        mc_rocket->visible = false;
    }
}