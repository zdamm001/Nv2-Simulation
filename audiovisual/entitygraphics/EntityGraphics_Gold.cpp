#include "EntityGraphics_Gold.h"
#include "..\\..\\simulation\\entities\\Entity_Gold.h"

EntityGraphics_Gold::EntityGraphics_Gold(Entity_Gold* entity, double posx, double posy)
    : entity(entity), anim(ANIM_NOT_COLLECTED) {
    mc = new MovieClip(); //new asset_gfx_gold()
    mc->x = posx;
    mc->y = posy;
    //mc->gotoAndStop("not_collected");
    mc->cacheAsBitmap = true;
}

EntityGraphics_Gold::~EntityGraphics_Gold() {
    delete mc;
}

void EntityGraphics_Gold::RegisterGraphics(vector<DisplayObject*>& graphics) {
    graphics.push_back(mc);
}

void EntityGraphics_Gold::UpdateState() {
    int prevAnim = anim;
    entity->GFX_UpdateState(this);
    if (anim != prevAnim) {
        if (anim == ANIM_COLLECTED) {
            mc->cacheAsBitmap = false;
            //mc->gotoAndPlay("collected");
        }
    }
}