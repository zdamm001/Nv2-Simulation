#include "EntityGraphics_Turret.h"
#include "../../simulation/entities/Entity_Turret.h"

EntityGraphics_Turret::EntityGraphics_Turret(Entity_Turret* entity, double x, double y)
    : entity(entity), anim_base(ANIM_IDLE), anim_crosshair(CROSSHAIR_OFF), pos_crosshair(0, 0) {
    mc_base = new MovieClip(); //new asset_gfx_turret();
    mc_base->x = x;
    mc_base->y = y;
    // mc_base->gotoAndStop("idle");
    mc_base->cacheAsBitmap = true;
    mc_crosshair = new MovieClip(); //new asset_gfx_turret_crosshair();
    // mc_crosshair->gotoAndStop("aim_off");
}

EntityGraphics_Turret::~EntityGraphics_Turret() {
    delete mc_base;
    delete mc_crosshair;
}

void EntityGraphics_Turret::RegisterGraphics(vector<DisplayObject*>& displayObjects) {
    displayObjects.insert(displayObjects.begin(), mc_base);
    displayObjects.push_back(mc_crosshair);
}

void EntityGraphics_Turret::UpdateState() {
    int prevAnimBase = anim_base;
    int prevAnimCrosshair = anim_crosshair;
    entity->GFX_UpdateState(this);
    
    if (anim_base != prevAnimBase) {
        if (anim_base == ANIM_IDLE) {
            // mc_base->gotoAndStop("idle");
        } else if (anim_base == ANIM_PREFIRE) {
            // mc_base->gotoAndPlay("prefire");
        } else if (anim_base == ANIM_POSTFIRE) {
            // mc_base->gotoAndPlay("postfire");
        } else if (anim_base == ANIM_FIRING) {
            // mc_base->gotoAndPlay("firing");
        }
    }
    
    mc_crosshair->x = pos_crosshair.x;
    mc_crosshair->y = pos_crosshair.y;
    
    if (anim_crosshair != prevAnimCrosshair) {
        if (anim_crosshair == CROSSHAIR_OFF) {
            // mc_crosshair->gotoAndStop("aim_off");
        } else if (anim_crosshair == CROSSHAIR_FAR) {
            // mc_crosshair->gotoAndStop("aim_far");
        } else if (anim_crosshair == CROSSHAIR_MID) {
            // mc_crosshair->gotoAndStop("aim_mid");
        } else if (anim_crosshair == CROSSHAIR_NEAR) {
            // mc_crosshair->gotoAndStop("aim_near");
        } else if (anim_crosshair == CROSSHAIR_PREFIRE) {
            // mc_crosshair->gotoAndStop("prefire");
        } else if (anim_crosshair == CROSSHAIR_POSTFIRE) {
            // mc_crosshair->gotoAndStop("postfire");
        }
    }
}