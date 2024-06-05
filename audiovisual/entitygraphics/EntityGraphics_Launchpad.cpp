#include "EntityGraphics_Launchpad.h"
#include "../../simulation/entities/Entity_Launchpad.h"

EntityGraphics_Launchpad::EntityGraphics_Launchpad(Entity_Launchpad* entity, double x, double y, double rotation)
    : entity(entity), anim(ANIM_IDLE) {
    mc = new MovieClip(); // new asset_gfx_launchpad();
    mc->x = x;
    mc->y = y;
    mc->rotation = rotation / M_PI * 180;
    // mc->gotoAndStop("idle");
    mc->cacheAsBitmap = true;
}

EntityGraphics_Launchpad::~EntityGraphics_Launchpad() {
    delete mc;
}

void EntityGraphics_Launchpad::RegisterGraphics(vector<DisplayObject*>& displayObjects) {
    displayObjects.insert(displayObjects.begin(), mc);
}

void EntityGraphics_Launchpad::UpdateState() {
    int prevAnim = anim;
    entity->GFX_UpdateState(this);
    if (anim != prevAnim) {
        if (anim == ANIM_LAUNCH) {
            // mc->gotoAndPlay("launch");
        }
    }
}