#include "EntityGraphics_Door_Trap.h"
#include "..\\..\\simulation\\entities\\Entity_Door_Trap.h"

EntityGraphics_Door_Trap::EntityGraphics_Door_Trap(Entity_Door_Trap* entity, double doorX, double doorY, double rotation, double switchX, double switchY)
    : entity(entity), anim(ANIM_CLOSE) {
    mc_door = new MovieClip(); //new asset_gfx_door_trap()
    mc_switch = new MovieClip(); //new asset_gfx_door_trap_switch();
    mc_door->x = doorX;
    mc_door->y = doorY;
    mc_door->rotation = rotation / M_PI * 180;
    //mc_door->gotoAndStop("opened");
    mc_switch->x = switchX;
    mc_switch->y = switchY;
    //mc_switch->gotoAndStop("open");
    mc_switch->cacheAsBitmap = true;
}

EntityGraphics_Door_Trap::~EntityGraphics_Door_Trap() {
    delete mc_door;
    delete mc_switch;
}

void EntityGraphics_Door_Trap::RegisterGraphics(vector<DisplayObject*>& displayObjects) {
    displayObjects.push_back(mc_door);
    displayObjects.insert(displayObjects.begin(), mc_switch);
}

void EntityGraphics_Door_Trap::UpdateState() {
    int prevAnim = anim;
    entity->GFX_UpdateState(this);
    if (anim != prevAnim) {
        if (anim == ANIM_OPEN) {
            //mc_door->gotoAndPlay("close");
            //mc_switch->gotoAndPlay("closed");
        }
    }
}