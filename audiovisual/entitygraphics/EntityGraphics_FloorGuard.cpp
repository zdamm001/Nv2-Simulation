#include "EntityGraphics_FloorGuard.h"
#include "..\\..\\simulation\\entities\\Entity_FloorGuard.h"

EntityGraphics_FloorGuard::EntityGraphics_FloorGuard(Entity_FloorGuard* entity)
    : entity(entity), anim(ANIM_IDLE) {
    mc = new MovieClip(); //new asset_gfx_floorguard()
    mc->cacheAsBitmap = true;
}

EntityGraphics_FloorGuard::~EntityGraphics_FloorGuard() {
    delete mc;
}

void EntityGraphics_FloorGuard::RegisterGraphics(vector<DisplayObject*>& graphics) {
    graphics.push_back(mc);
}

void EntityGraphics_FloorGuard::UpdateState() {
    int prevAnim = anim;
    entity->GFX_UpdateState(this);
    mc->x = pos.x;
    mc->y = pos.y;
    if (anim != prevAnim) {
        if (anim == ANIM_CHASE_L || anim == ANIM_CHASE_R) {
            //mc->gotoAndPlay("chase");
        }
        else {
            //mc->gotoAndStop("idle");
        }
    }
}