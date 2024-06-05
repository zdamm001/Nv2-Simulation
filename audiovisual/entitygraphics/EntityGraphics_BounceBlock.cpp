#include "EntityGraphics_BounceBlock.h"
#include "..\\..\\simulation\\entities\\Entity_BounceBlock.h"

EntityGraphics_BounceBlock::EntityGraphics_BounceBlock(Entity_BounceBlock* entity)
    : entity(entity) {
    mc = new MovieClip(); //new asset_gfx_bounceblock()
    mc->cacheAsBitmap = true;
}

EntityGraphics_BounceBlock::~EntityGraphics_BounceBlock() {
    delete mc;
}

void EntityGraphics_BounceBlock::RegisterGraphics(vector<DisplayObject*>& graphics) {
    graphics.push_back(mc);
}

void EntityGraphics_BounceBlock::UpdateState() {
    entity->GFX_UpdateState(this);
    mc->x = pos.x;
    mc->y = pos.y;
}