#include "EntityGraphics_Door_Locked.h"
#include "..\\..\\simulation\\entities\\Entity_Door_Locked.h"

EntityGraphics_Door_Locked::EntityGraphics_Door_Locked(Entity_Door_Locked* entity, double doorX, double doorY, double rotation, double switchX, double switchY)
    : entity(entity), anim(ANIM_CLOSE) {
    mc_door = new MovieClip(); //new asset_gfx_door_locked()
    mc_switch = new MovieClip();//new asset_gfx_door_locked_switch();
    mc_door->x = doorX;
    mc_door->y = doorY;
    mc_door->rotation = rotation / M_PI * 180;
    //mc_door->gotoAndStop("closed");
    mc_switch->x = switchX;
    mc_switch->y = switchY;
    //mc_switch->gotoAndStop("closed");
    mc_switch->cacheAsBitmap = true;
}

EntityGraphics_Door_Locked::~EntityGraphics_Door_Locked() {
    delete mc_door;
    delete mc_switch;
}

void EntityGraphics_Door_Locked::RegisterGraphics(vector<DisplayObject*>& displayObjects) {
    displayObjects.push_back(mc_door);
    displayObjects.insert(displayObjects.begin(), mc_switch);
}

void EntityGraphics_Door_Locked::UpdateState() {
    int prevAnim = anim;
    entity->GFX_UpdateState(this);
    if (anim != prevAnim) {
        if (anim == ANIM_OPEN) {
            //mc_door->gotoAndPlay("open");
            //mc_switch->gotoAndPlay("open");
        }
    }
}