#include "EntityGraphics_Mine.h"
#include "..\\..\\simulation\\entities\\Entity_Mine.h"

EntityGraphics_Mine::EntityGraphics_Mine(Entity_Mine* entity, double x, double y)
    : entity(entity), anim(ANIM_UNEXPLODED) {
    mc = new MovieClip(); //new asset_gfx_mine()
    mc->x = x;
    mc->y = y;
    //mc->gotoAndStop("unexploded");
    mc->cacheAsBitmap = true;
}

EntityGraphics_Mine::~EntityGraphics_Mine() {
    delete mc;
}

void EntityGraphics_Mine::RegisterGraphics(vector<DisplayObject*>& graphics) {
    graphics.push_back(mc);
}

void EntityGraphics_Mine::UpdateState() {
    int prevAnim = anim;
    entity->GFX_UpdateState(this);
    if (anim != prevAnim) {
        if (anim == ANIM_EXPLODED) {
            mc->cacheAsBitmap = false;
            //mc->gotoAndPlay("exploded");
        }
    }
}